#include "Descriptor.h"
#include "../Device/Device.h"
#include <d3d12.h>
#include <crtdbg.h>


//ヒープ生成
void create::CreateHeap(ID3D12DescriptorHeap** heap, const D3D12_DESCRIPTOR_HEAP_TYPE& type, const D3D12_DESCRIPTOR_HEAP_FLAGS& flag, const size_t& num)
{
	D3D12_DESCRIPTOR_HEAP_DESC desc{};

	desc.Flags			= flag;
	//ヒープ内の記述子の数
	desc.NumDescriptors = unsigned int(num);
	//ヒープ内の記述子のタイプを指定
	desc.Type			= type;

	auto hr = Device::Get().Dev()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&(*heap)));
	_ASSERT(hr == S_OK);
}

//リソース生成
void create::CreateRsc(ID3D12Resource** rsc, const D3D12_HEAP_PROPERTIES& prop, const D3D12_RESOURCE_DESC& desc, const D3D12_CLEAR_VALUE* clear,
					   const D3D12_RESOURCE_STATES& state, const D3D12_HEAP_FLAGS& flag)
{
	auto hr = Device::Get().Dev()->CreateCommittedResource(&prop, flag, &desc, state, clear, IID_PPV_ARGS(&(*rsc)));
	_ASSERT(hr == S_OK);
}

//RTV生成
void create::RTV(ID3D12Resource* rsc, ID3D12DescriptorHeap* heap, const size_t& index)
{
	D3D12_RENDER_TARGET_VIEW_DESC desc{};

	//表示形式の指定
	desc.Format				= rsc->GetDesc().Format;
	//レンダーターゲットリソースへのアクセス方法を指定
	desc.ViewDimension		= D3D12_RTV_DIMENSION::D3D12_RTV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipSlice = 0;

	//ヒープ開始
	auto handle = heap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr = Device::Get().Dev()->GetDescriptorHandleIncrementSize(heap->GetDesc().Type) * index;

	Device::Get().Dev()->CreateRenderTargetView(rsc, &desc, handle);
}

// マップ
void create::Map(ID3D12Resource* rsc, void** data)
{
	D3D12_RANGE range{ 0, 1 };
	auto hr = rsc->Map(0, &range, *(&data));
	_ASSERT(hr == S_OK);
}

// アンマップ
void create::UnMap(ID3D12Resource* rsc)
{
	D3D12_RANGE range{ 0, 1 };
	rsc->Unmap(0, &range);
}