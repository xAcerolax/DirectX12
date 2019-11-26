#include "Manager.h"
#include "..//Graphics/List/List.h"
#include "../Graphics/RootSignature/RootSignature.h"
#include "../Graphics/Pipeline/Pipeline.h"
#include "../Graphics/Texture/Texture.h"
#include "../Graphics/Primitive/Primitive.h"
#include "../Func/Func.h"
#include "../resource/resource.h"
#include <d3d12.h>

// インプット一覧
const D3D12_INPUT_ELEMENT_DESC inputs[] = {
	//0
	{ "POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION::D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	//1
	{ "TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,       0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION::D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	//2	
	{ "NORMAL",   0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION::D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	//3
	{ "BORN",     0, DXGI_FORMAT::DXGI_FORMAT_R16G16_UINT,        0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION::D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	//4
	{ "WEIGHT",   0, DXGI_FORMAT::DXGI_FORMAT_R8_UINT,            0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION::D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
};

//コンストラクタ
Manager::Manager() :
	target("メイン")
{
#ifdef  _DEBUG
	Microsoft::WRL::ComPtr<ID3D12Debug>debug = nullptr;
	D3D12GetDebugInterface(IID_PPV_ARGS(&debug));
	debug->EnableDebugLayer();

#endif //  _DEBUG
	Init();
}

//デストラクタ
Manager::~Manager()
{
	CoUninitialize();
}

//ルート生成
template <typename T>
void Manager::CreateRoot(const std::string& name, const std::initializer_list<T>& id, const bool& geoFlag)
{
	if (root.find(name) == root.end())
	{
		root[name] = std::make_shared<RootSignature>();
		auto itr = id.begin();

		while (itr != id.end())
		{
			root[name]->Vertex("Shader/Shader.hlsl", "Shader", "fx_5_1");
			++itr;
		}
	}
}
template void Manager::CreateRoot(const std::string&, const std::initializer_list<std::string>&, const bool&);

//パイプ生成
void Manager::CreatePipe(const std::string& name, std::weak_ptr<RootSignature>root, const std::initializer_list<unsigned char>& index
	, const D3D12_PRIMITIVE_TOPOLOGY_TYPE& type, const bool& depth)
{
	if (pipe.find(name) == pipe.end())
	{
		std::vector<D3D12_INPUT_ELEMENT_DESC> input;

		for (const unsigned char& i : index)
		{
			input.push_back(inputs[i]);
		}
		pipe[name] = std::make_shared<Pipeline>(root, *input.data(), input.size(), type, depth);
	}
}

//初期化
void Manager::Init(void)
{
	auto hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	_ASSERT(hr == S_OK);

	CreateRoot("tex", {TexVertex}, true);
	CreatePipe("tex", root["tex"], { 0,1 }, D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE);

	CreateRoot("prim", { PrimVertex, PrimPixel });
	CreatePipe("point",		root["prim"], { 0 }, D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT);
	CreatePipe("line",		root["prim"], { 0 }, D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE);
	CreatePipe("triangle",	root["prim"], { 0 }, D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE);
}

//初期化
bool Manager::InitLib(const Vec2& size, const Vec2& pos, const std::string& parent)
{
	if (lib.find(target) == lib.end())
	{
		MainLib* temp = nullptr;
		
		if (lib.find(parent) !=lib.end())
		{
			temp = &(*lib[parent]);
		}
		lib[target] = std::make_shared<MainLib>(size, pos, temp);

		return true;
	}
	return false;
}

// 画像読み込み
int Manager::LoadImg(const std::string& fileName)
{
	int id = create::Random(1, 99999);

	while (tex.find(id) != tex.end())
	{
		id = create::Random(1, 99999);
	}

	tex[id] = std::make_shared<Texture>(fileName);

	return id;
}

// 画面クリア
void Manager::Clear(void)
{
	lib[target]->Clear();
}

// 本来の画像サイズで描画
void Manager::DrawImg(const int& id, const Vec2f& pos, const float& angle, const bool& turnX, const bool& turnY, const float& alpha)
{
	lib[target]->GetList().lock()->Get()->SetGraphicsRootSignature(root["tex"]->Get());
	lib[target]->GetList().lock()->Get()->SetPipelineState(pipe["tex"]->Get());

	lib[target]->SetDraw();
	tex[id]->DrawImg(pos, angle, turnX, turnY, alpha);
	tex[id]->Draw(lib[target]->GetList());
}

// 指定した画像サイズで描画
void Manager::DrawImgRect(const int& id, const Vec2f& pos, const Vec2f& size, const float& angle, const bool& turnX, const bool& turnY, const float& alpha)
{
	lib[target]->GetList().lock()->Get()->SetGraphicsRootSignature(root["tex"]->Get());
	lib[target]->GetList().lock()->Get()->SetPipelineState(pipe["tex"]->Get());

	lib[target]->SetDraw();
	tex[id]->DrawRect(pos, size, angle, turnX, turnY, alpha);
	tex[id]->Draw(lib[target]->GetList());
}

// 指定した画像サイズで指定した矩形に分割して描画
void Manager::DrawImgDivide(const int& id, const Vec2f& pos, const Vec2f& size, const Vec2f& uvPos, const Vec2f& uvSize,
	const float& angle, const bool& turnX, const bool& turnY, const float& alpha)
{
	lib[target]->GetList().lock()->Get()->SetGraphicsRootSignature(root["tex"]->Get());
	lib[target]->GetList().lock()->Get()->SetPipelineState(pipe["tex"]->Get());

	lib[target]->SetDraw();
	tex[id]->DrawDivide(pos, size, uvPos, uvSize, angle, turnX, turnY, alpha);
	tex[id]->Draw(lib[target]->GetList());
}

// ポイント描画
void Manager::DrawPoint(const Vec2f& pos, const float& r, const float& g, const float& b, const float& a)
{
	lib[target]->GetList().lock()->Get()->SetGraphicsRootSignature(root["prim"]->Get());
	lib[target]->GetList().lock()->Get()->SetPipelineState(pipe["point"]->Get());

	prim.push_back(std::make_shared<Primitive>(lib[target]->GetList(), create::PrimType::POINT));
	lib[target]->SetDraw();
	(*prim.rbegin())->DrawPoint(pos, create::Color(r, g, b, a));
	(*prim.rbegin())->Draw();
}

// ライン描画
void Manager::DrawLine(const Vec2f& pos1, const Vec2f& pos2, const float& r, const float& g, const float& b, const float& a)
{
	lib[target]->GetList().lock()->Get()->SetGraphicsRootSignature(root["prim"]->Get());
	lib[target]->GetList().lock()->Get()->SetPipelineState(pipe["line"]->Get());

	prim.push_back(std::make_shared<Primitive>(lib[target]->GetList(), create::PrimType::LINE));
	lib[target]->SetDraw();
	(*prim.rbegin())->DrawLine(pos1, pos2, create::Color(r, g, b, a));
	(*prim.rbegin())->Draw();
}

// トライアングル描画
void Manager::DrawTriangle(const Vec2f& pos1, const Vec2f& pos2, const Vec2f& pos3, const float& r, const float& g, const float& b, const float& a)
{
	lib[target]->GetList().lock()->Get()->SetGraphicsRootSignature(root["prim"]->Get());
	lib[target]->GetList().lock()->Get()->SetPipelineState(pipe["triangle"]->Get());

	prim.push_back(std::make_shared<Primitive>(lib[target]->GetList(), create::PrimType::TRIANGLE));
	lib[target]->SetDraw();
	(*prim.rbegin())->DrawTriangle(pos1, pos2, pos3, create::Color(r, g, b, a));
	(*prim.rbegin())->Draw();
}

// ボックス描画
void Manager::DrawBox(const Vec2f& pos, const Vec2f& size, const float& r, const float& g, const float& b, const float& a)
{
	lib[target]->GetList().lock()->Get()->SetGraphicsRootSignature(root["prim"]->Get());
	lib[target]->GetList().lock()->Get()->SetPipelineState(pipe["triangle"]->Get());

	prim.push_back(std::make_shared<Primitive>(lib[target]->GetList(), create::PrimType::BOX));
	lib[target]->SetDraw();
	(*prim.rbegin())->DrawBox(pos, size, create::Color(r, g, b, a));
	(*prim.rbegin())->Draw();
}

// 実行
void Manager::Execution(void)
{
	lib[target]->Execution();
}

// テクスチャハンドルの削除
void Manager::DeleteTex(const int& id)
{
	if (tex.find(id) != tex.end())
	{
		tex.erase(tex.find(id));
	}
}

// プリミティブデータの削除
void Manager::DeletePrim(const bool& memReset)
{
	prim.clear();
	if (memReset == true)
	{
		prim.shrink_to_fit();
	}
}

// ライブラリのターゲット切り替え
void Manager::ChangeTarget(const std::string& name)
{
	target = name;
}

// ライブラリターゲットの取得
std::string Manager::GetTarget(void) const
{
	return target;
}