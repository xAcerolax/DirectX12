#include "RootSignature.h"
#include "Device.h"
#include "Func.h"
#include <d3dcompiler.h>
#include <d3d12.h>
#include <crtdbg.h>
#include <functional>
#include <unordered_map>
#include <dxcapi.h>

//コンストラクタ
RootSignature::RootSignature() :
	root(nullptr), vertex(nullptr), geometry(nullptr), pixel(pixel), compute(nullptr)
{
}

//デストラクタ
RootSignature::~RootSignature()
{
}

//シェーダーコンパイル
void read::ShaderCompile(const std::string& fileName, const std::string& func, const std::string& ver, ID3DBlob** blob)
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
		Microsoft::WRL::ComPtr<IDxcBlobEncoding> print = nullptr;
		Microsoft::WRL::ComPtr<IDxcBlobEncoding> print16 = nullptr;

		hr = result->GetErrorBuffer(&print);
		_ASSERT(hr == S_OK);

		hr = library->GetBlobAsUtf16(print.Get(), &print16);
		_ASSERT(hr == S_OK);

		wprintf(L"%*s", (int)print16->GetBufferSize() / 2, (LPCWSTR)print16->GetBufferPointer());
	}
}

//.cso読み込み
void read::ShaderLoad(const std::string& fileName, ID3DBlob** blob)
{
	auto path = create::ChangeCode(fileName);
	auto hr = D3DReadFileToBlob(path.c_str(), blob);
	_ASSERT(hr == S_OK);
}

//リソース読み込み
void read::ShaderRead(const int& id, ID3DBlob** blob)
{
	HRSRC rsc = FindResource(nullptr, MAKEINTRESOURCE(id), (LPCSTR)L"Shader");
	_ASSERT(rsc != nullptr);
	HANDLE handle = LoadResource(nullptr, rsc);
	_ASSERT(handle != nullptr);

	void* data = LockResource(handle);
	size_t size = SizeofResource(nullptr, rsc);

	auto hr = D3DSetBlobPart(data, size, D3D_BLOB_PART::D3D_BLOB_PRIVATE_DATA, 0, data, size, blob);
	_ASSERT(hr == S_OK);
}

//ルートシグネチャ生成
void RootSignature::CreateRoot(ID3DBlob* blob)
{
	Microsoft::WRL::ComPtr<ID3DBlob>sig = nullptr;
	auto hr = D3DGetBlobPart(blob->GetBufferPointer(), blob->GetBufferSize(), D3D_BLOB_PART::D3D_BLOB_ROOT_SIGNATURE, 0, &sig);
	_ASSERT(hr == S_OK);

	hr = Device::Get().Dev()->CreateRootSignature(0, sig->GetBufferPointer(), sig->GetBufferSize(), IID_PPV_ARGS(&root));
	_ASSERT(hr == S_OK);
}


//--------------------------------------------
//	コンパイル
//--------------------------------------------

//頂点シェーダ
void RootSignature::Vertex(const std::string& fileName, const std::string& func, const std::string& ver)
{
	read::ShaderCompile(fileName, func, ver, &vertex);
	CreateRoot(vertex.Get());
}

//ジオメトリシェーダ
void RootSignature::Geometry(const std::string& fileName, const std::string& func, const std::string& ver)
{
	read::ShaderCompile(fileName, func, ver, &geometry);
}

//ピクセルシェーダ
void RootSignature::Pixel(const std::string& fileName, const std::string& func, const std::string& ver)
{
	read::ShaderCompile(fileName, func, ver, &pixel);
}

//コンピュートシェーダ
void RootSignature::Compute(const std::string& fileName, const std::string& func, const std::string& ver)
{
	read::ShaderCompile(fileName, func, ver, &compute);
	CreateRoot(compute.Get());
}


//--------------------------------------------
//	.csoの読み込み
//--------------------------------------------

//頂点シェーダの.cso読み込み
void RootSignature::Vertex(const std::string& fileName)
{
	read::ShaderLoad(fileName, &vertex);
	CreateRoot(vertex.Get());
}

//ジオメトリシェーダの.cso読み込み
void RootSignature::Geometry(const std::string& fileName)
{
	read::ShaderLoad(fileName, &geometry);
}

//ピクセルシェーダの.cso読み込み
void RootSignature::Pixel(const std::string& fileName)
{
	read::ShaderLoad(fileName, &pixel);
}

//コンピュートシェーダの.cso読み込み
void RootSignature::Compute(const std::string& fileName)
{
	read::ShaderLoad(fileName, &compute);
	CreateRoot(compute.Get());
}


//--------------------------------------------
//	リソースの読み込み
//--------------------------------------------

//頂点シェーダ
void RootSignature::Vertex(const int& id)
{
	read::ShaderRead(id, &vertex);
	CreateRoot(vertex.Get());
}

//ジオメトリシェーダ
void RootSignature::Geometry(const int& id)
{
	read::ShaderRead(id, &geometry);
}

//ピクセルシェーダ
void RootSignature::Pixel(const int& id)
{
	read::ShaderRead(id, &pixel);
}

//コンピュートシェーダ
void RootSignature::Compute(const int& id)
{
	read::ShaderRead(id, &compute);
	CreateRoot(compute.Get());
}


//--------------------------------------------
//	情報取得
//--------------------------------------------

ID3D12RootSignature* RootSignature::Get(void) const
{
	return root.Get();
}

//頂点シェーダ
ID3DBlob* RootSignature::GetVertex(void) const
{
	return vertex.Get();
}

// ジオメトリシェーダ
ID3DBlob* RootSignature::GetGeometry(void) const
{
	return geometry.Get();
}

// ピクセルシェーダ
ID3DBlob* RootSignature::GetPixel(void) const
{
	return pixel.Get();
}

// コンピュートシェーダ
ID3DBlob* RootSignature::GetCompute(void) const
{
	return compute.Get();
}