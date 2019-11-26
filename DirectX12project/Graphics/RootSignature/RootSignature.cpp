#include "RootSignature.h"
#include "../Device/Device.h"
#include "../../Func/Func.h"
#include <d3dcompiler.h>
#include <d3d12.h>
#include <crtdbg.h>
#include <functional>
#include <unordered_map>


// シェーダコンパイル
void create::ShaderCompile(const std::string& fileName, const std::string& func, const std::string& ver, ID3DBlob** blob)
{
	auto path = create::ChangeCode(fileName);
	auto hr = D3DCompileFromFile(path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, func.c_str(), ver.c_str(),
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, *(&blob), nullptr);
	_ASSERT(hr == S_OK);
}

// .cso読み込み
void create::ShaderLoad(const std::string& fileName, ID3DBlob** blob)
{
	auto path = create::ChangeCode(fileName);
	auto hr = D3DReadFileToBlob(path.c_str(), blob);
	_ASSERT(hr == S_OK);
}

// リソース読み込み
void create::ShaderRead(const int& id, ID3DBlob** blob)
{
	HRSRC rsc = FindResource(nullptr, MAKEINTRESOURCE(id), L"Shader");
	_ASSERT(rsc != nullptr);

	HANDLE handle = LoadResource(nullptr, rsc);
	_ASSERT(handle != nullptr);

	void* data = LockResource(handle);
	size_t size = SizeofResource(nullptr, rsc);

	auto hr = D3DSetBlobPart(data, size, D3D_BLOB_PART::D3D_BLOB_PRIVATE_DATA, 0, data, size, blob);
	_ASSERT(hr == S_OK);
}

// コンストラクタ
RootSignature::RootSignature() :
	root(nullptr), vertex(nullptr), geometry(nullptr), pixel(nullptr), compute(nullptr)
{
}

// デストラクタ
RootSignature::~RootSignature()
{
}

// ルートシグネチャ生成
void RootSignature::CreateRoot(ID3DBlob* blob)
{
	Microsoft::WRL::ComPtr<ID3DBlob>sig = nullptr;
	auto hr = D3DGetBlobPart(blob->GetBufferPointer(), blob->GetBufferSize(), D3D_BLOB_PART::D3D_BLOB_ROOT_SIGNATURE, 0, &sig);
	_ASSERT(hr == S_OK);

	hr = Device::Get().Dev()->CreateRootSignature(0, sig->GetBufferPointer(), sig->GetBufferSize(), IID_PPV_ARGS(&root));
	_ASSERT(hr == S_OK);
}

// 頂点シェーダコンパイル
void RootSignature::Vertex(const std::string& fileName, const std::string& func, const std::string& ver)
{
	create::ShaderCompile(fileName, func, ver, &vertex);
	CreateRoot(vertex.Get());
}

// ジオメトリーシェーダコンパイル
void RootSignature::Geometry(const std::string& fileName, const std::string& func, const std::string& ver)
{
	create::ShaderCompile(fileName, func, ver, &geometry);
}

// ピクセルシェーダコンパイル
void RootSignature::Pixel(const std::string& fileName, const std::string& func, const std::string& ver)
{
	create::ShaderCompile(fileName, func, ver, &pixel);
}

// コンピュートシェーダコンパイル
void RootSignature::Compute(const std::string& fileName, const std::string& func, const std::string& ver)
{
	create::ShaderCompile(fileName, func, ver, &compute);
	CreateRoot(compute.Get());
}

// 頂点シェーダの.cso読み込み
void RootSignature::Vertex(const std::string& fileName)
{
	create::ShaderLoad(fileName, &vertex);
	CreateRoot(vertex.Get());
}

// ジオメトリシェーダの.cso読み込み
void RootSignature::Geometry(const std::string& fileName)
{
	create::ShaderLoad(fileName, &geometry);
}

// ピクセルシェーダの.cso読み込み
void RootSignature::Pixel(const std::string& fileName)
{
	create::ShaderLoad(fileName, &pixel);
}

// コンピュートシェーダの.cso読み込み
void RootSignature::Compute(const std::string& fileName)
{
	create::ShaderLoad(fileName, &compute);
	CreateRoot(compute.Get());
}

// 頂点シェーダのリソース読み込み
void RootSignature::Vertex(const int& id)
{
	create::ShaderRead(id, &vertex);
	CreateRoot(vertex.Get());
}

// ジオメトリシェーダのリソース読み込み
void RootSignature::Geometry(const int& id)
{
	create::ShaderRead(id, &geometry);
}

// ピクセルシェーダのリソース読み込み
void RootSignature::Pixel(const int& id)
{
	create::ShaderRead(id, &pixel);
}

// コンピュートシェーダのリソース読み込み
void RootSignature::Compute(const int& id)
{
	create::ShaderRead(id, &compute);
	CreateRoot(compute.Get());
}

// ルートシグネチャ取得
ID3D12RootSignature* RootSignature::Get(void) const
{
	return root.Get();
}

// 頂点シェーダ情報取得
ID3DBlob* RootSignature::GetVertex(void) const
{
	return vertex.Get();
}

// ジオメトリシェーダ情報取得
ID3DBlob* RootSignature::GetGeometry(void) const
{
	return geometry.Get();
}

// ピクセルシェーダ情報取得
ID3DBlob* RootSignature::GetPixel(void) const
{
	return pixel.Get();
}

// コンピュートシェーダ情報取得
ID3DBlob* RootSignature::GetCompute(void) const
{
	return compute.Get();
}