#include "Render.h"
#include "Deccriptor.h"
#include "SwapChain.h"
#include "Device.h"
#include "CommandMng.h"
#include <d3d12.h>
#include <crtdbg.h>
#include <dxgi1_6.h>

//クリア画面色
const float color[] = {
	1.0f,
	1.0f,
	1.0f,
	1.0f
};

//コンストラクタ
Render::Render(std::weak_ptr<SwapChain>swap) :
	swap(swap), heap(nullptr)
{

}

//デストラクタ
Render::~Render()
{
}

//ヒープの生成
void Render::CreateHeap(void)
{
	create::CreateHeap(&heap, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_RTV, D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_NONE, swap.lock()->GetBack());
	rsc.resize(swap.lock()->GetBack());
}

//リソースの生成
void Render::CreateRsc(void)
{
	for (size_t i = 0; i < rsc.size(); ++i)
	{
		auto hr = swap.lock()->Get()->GetBuffer(unsigned int(i), IID_PPV_ARGS(&rsc[i]));
		_ASSERT(hr == S_OK);

		create::RTV(rsc[i].Get(), heap.Get(), i);
	}
}

//画面クリア
void Render::Clear(std::weak_ptr<CommandMng> command, ID3D12DescriptorHeap* depth)
{
	auto rtv = heap->GetCPUDescriptorHandleForHeapStart();
	rtv.ptr += Device::Get().Dev()->GetDescriptorHandleIncrementSize(heap->GetDesc().Type)
		* swap.lock()->Get()->GetCurrentBackBufferIndex();
	std::unique_ptr<D3D12_CPU_DESCRIPTOR_HANDLE> dsv = nullptr;

	if (depth != nullptr)
	{
		dsv = std::make_unique< D3D12_CPU_DESCRIPTOR_HANDLE>();
		(*dsv) = depth->GetCPUDescriptorHandleForHeapStart();
	}

	/*command.lock()->Get()->OMSetRenderTargets(1, &rtv, false, &(*dsv));

	command.lock()->Get()->ClearRenderTargetView(rtv, color, 0, nullptr);*/
}

//リソースの取得
ID3D12Resource* Render::Get(void) const
{
	return rsc[swap.lock()->Get()->GetCurrentBackBufferIndex()].Get();
}


