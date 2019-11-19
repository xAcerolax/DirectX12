#include "RootSignature.h"
#include "Device.h"
#include "Func.h"
#include <d3dcompiler.h>
#include <d3d12.h>
#include <crtdbg.h>
#include <functional>
#include <unordered_map>
#include <dxcapi.h>


RootSignature::RootSignature()
{
}

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

void read::ShaderLoad(const std::string& fileName, ID3DBlob** blob)
{
}

void read::ShaderRead(const int& id, ID3DBlob** blob)
{
}

void RootSignature::CreateRoot(ID3DBlob* blob)
{
}

void RootSignature::Vertex(const std::string& fileName, const std::string& func, const std::string& ver)
{
}

void RootSignature::Geometry(const std::string& fileName, const std::string& func, const std::string& ver)
{
}

void RootSignature::Pixel(const std::string& fileName, const std::string& func, const std::string& ver)
{
}

void RootSignature::Compute(const std::string& fileName, const std::string& func, const std::string& ver)
{
}

void RootSignature::Vertex(const std::string& fileName)
{
}

void RootSignature::Geometry(const std::string& fileName)
{
}

void RootSignature::Pixel(const std::string& fileName)
{
}

void RootSignature::Compute(const std::string& fileName)
{
}

void RootSignature::Vertex(const int& id)
{
}

void RootSignature::Geometry(const int& id)
{
}

void RootSignature::Pixel(const int& id)
{
}

void RootSignature::Compute(const int& id)
{
}

ID3D12RootSignature* RootSignature::Get(void) const
{
	return nullptr;
}

ID3DBlob* RootSignature::GetVertex(void) const
{
	return nullptr;
}

ID3DBlob* RootSignature::GetGeometry(void) const
{
	return nullptr;
}

ID3DBlob* RootSignature::GetPixel(void) const
{
	return nullptr;
}

ID3DBlob* RootSignature::GetCompute(void) const
{
	return nullptr;
}