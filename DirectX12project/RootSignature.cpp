#include "RootSignature.h"
#include "Device.h"
#include "Func.h"
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
#include <d3d12.h>
#pragma comment(lib, "d3d12.lib")
#include <crtdbg.h>
#include <functional>
#include <unordered_map>
#include <dxcapi.h>


// シェーダコンパイル
void create::ShaderCompile(const std::string& fileName, const std::string& func, const std::string& ver, ID3DBlob** blob)
{
	auto path = create::ChangeCode(fileName);
	auto entry = create::ChangeCode(func);
	auto model = create::ChangeCode(ver);

	Microsoft::WRL::ComPtr<IDxcLibrary>library = nullptr;
	auto hr = DxcCreateInstance(CLSID_DxcLibrary, IID_PPV_ARGS(&library));
	_ASSERT(hr == S_OK);

	Microsoft::WRL::ComPtr<IDxcIncludeHandler>handler = nullptr;
	hr = library->CreateIncludeHandler(&handler);
	_ASSERT(hr == S_OK);

	Microsoft::WRL::ComPtr<IDxcBlobEncoding>encode = nullptr;
	hr = library->CreateBlobFromFile(path.c_str(), nullptr, &encode);
	_ASSERT(hr == S_OK);

	LPCWSTR arg[] = { L"/Zi" };
	Microsoft::WRL::ComPtr<IDxcCompiler>compiler = nullptr;
	hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&compiler));
	_ASSERT(hr == S_OK);
	Microsoft::WRL::ComPtr<IDxcOperationResult>result = nullptr;
	hr = compiler->Compile(encode.Get(), path.c_str(), entry.c_str(), model.c_str(), arg, _countof(arg), nullptr, 0, handler.Get(), &result);
	_ASSERT(hr == S_OK);

	result->GetStatus(&hr);
	if (SUCCEEDED(hr))
	{
		hr = result->GetResult((IDxcBlob**) & (*blob));
		_ASSERT(hr == S_OK);
	}
	else
	{
		Microsoft::WRL::ComPtr<IDxcBlobEncoding>print = nullptr;
		Microsoft::WRL::ComPtr<IDxcBlobEncoding>print16 = nullptr;

		hr = result->GetErrorBuffer(&print);
		_ASSERT(hr == S_OK);

		hr = library->GetBlobAsUtf16(print.Get(), &print16);
		_ASSERT(hr == S_OK);

		wprintf(L"%*s", (int)print16->GetBufferSize() / 2, (LPCWSTR)print16->GetBufferPointer());
	}
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
	HRSRC rsc = FindResource(nullptr, MAKEINTRESOURCE(id), "Shader");
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