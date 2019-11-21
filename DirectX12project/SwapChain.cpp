#include "SwapChain.h"
#include "Window.h"
#include "Queue.h"
#include <crtdbg.h>
#include <dxgi1_6.h>


unsigned int SwapChain::bufferCnt = 3;

// �R���X�g���N�^
SwapChain::SwapChain(std::weak_ptr<Window>win, std::weak_ptr<Queue>queue) :
	window(window), queue(queue), swap(nullptr)
{
	CreateSwap();
}

// �f�X�g���N�^
SwapChain::~SwapChain()
{
}

// �X���b�v�`�F�C���̐���
void SwapChain::CreateSwap(void)
{
	Microsoft::WRL::ComPtr<IDXGIFactory7>factory = nullptr;
	auto hr = CreateDXGIFactory(IID_PPV_ARGS(&factory));
	_ASSERT(hr == S_OK);

	//�E�B���h�E�T�C�Y
	RECT winSize{};
	GetClientRect(HWND(window.lock()->Get()), &winSize);

	DXGI_SWAP_CHAIN_DESC1 desc{};
	desc.AlphaMode = DXGI_ALPHA_MODE::DXGI_ALPHA_MODE_UNSPECIFIED;
	desc.BufferCount = bufferCnt;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.Height = winSize.bottom;
	desc.SampleDesc = { 1, 0 };
	desc.Scaling = DXGI_SCALING::DXGI_SCALING_STRETCH;
	desc.Stereo = false;
	desc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
	desc.Width = winSize.right;

	hr = factory->CreateSwapChainForHwnd((IUnknown*)queue.lock()->Get(), HWND(window.lock()->Get()), &desc, nullptr, nullptr, (IDXGISwapChain1**)swap.GetAddressOf());
	_ASSERT(hr == S_OK);
}

IDXGISwapChain4* SwapChain::Get(void) const
{
	return swap.Get();
}