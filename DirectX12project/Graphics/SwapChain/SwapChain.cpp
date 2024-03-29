#include "SwapChain.h"
#include "../../Window/Window.h"
#include "../Queue/Queue.h"
#include <crtdbg.h>
#include <dxgi1_6.h>


unsigned int SwapChain::bufferCnt = 3;

// コンストラクタ
SwapChain::SwapChain(std::weak_ptr<Window>window, std::weak_ptr<Queue>queue) :
	window(window), queue(queue), swap(nullptr)
{
	CreateSwap();
}

// デストラクタ
SwapChain::~SwapChain()
{
}

// スワップチェインの生成
void SwapChain::CreateSwap(void)
{
	//※
	Microsoft::WRL::ComPtr<IDXGIFactory2>factory = nullptr;
	auto hr = CreateDXGIFactory(IID_PPV_ARGS(&factory));
	_ASSERT(hr == S_OK);


	//ウィンドウサイズ
	RECT winSize{};
	GetClientRect(HWND(window.lock()->Get()), &winSize);

	DXGI_SWAP_CHAIN_DESC1 desc{};
	desc.AlphaMode = DXGI_ALPHA_MODE::DXGI_ALPHA_MODE_UNSPECIFIED;
	desc.BufferCount = bufferCnt;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.Height = winSize.bottom;
	desc.Width = winSize.right;
	desc.SampleDesc = { 1, 0 };
	desc.Scaling = DXGI_SCALING::DXGI_SCALING_STRETCH;
	desc.Stereo = false;
	desc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
	

	hr = factory->CreateSwapChainForHwnd((IUnknown*)queue.lock()->Get(), HWND(window.lock()->Get()), &desc, nullptr, nullptr, (IDXGISwapChain1**)swap.GetAddressOf());
	_ASSERT(hr == S_OK);
}

IDXGISwapChain4* SwapChain::Get(void) const
{
	return swap.Get();
}