#include "SwapChain.h"
#include "Window.h"
#include "Queue.h"
#include <crtdbg.h>
#include <dxgi1_6.h>


SwapChain::SwapChain(std::weak_ptr<Window> window, std::weak_ptr<Queue> queue) :
	window(window), queue(queue), swap(nullptr)
{
	CreateSwap();
}

SwapChain::~SwapChain()
{
}

void SwapChain::CreateSwap()
{
	bufferCnt = 3;

	Microsoft::WRL::ComPtr<IDXGIFactory7>factory = nullptr;
	auto hr = CreateDXGIFactory(IID_PPV_ARGS(&factory));

	//����]�����A���ʂ�False�̏ꍇ�̓f�o�b�O���|�[�g�𐶐�
	_ASSERT(hr == S_OK);	

	//�E�B���h�E�T�C�Y
	RECT windowSize{};
	GetClientRect(HWND(window.lock()->Get()), &windowSize);

	//�X���b�v�`�F�C���ݒ�p�\����
	DXGI_SWAP_CHAIN_DESC1 desc = {};

	desc.AlphaMode		= DXGI_ALPHA_MODE::DXGI_ALPHA_MODE_UNSPECIFIED;
	desc.BufferCount	= bufferCnt;
	desc.BufferUsage	= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.Flags			= 0;
	desc.Format			= DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;;
	desc.Height			= windowSize.bottom;
	desc.Width			= windowSize.right;
	desc.SampleDesc		= { 1,0 };
	desc.Scaling		= DXGI_SCALING::DXGI_SCALING_STRETCH;
	desc.Stereo			= false;
	desc.SwapEffect		= DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;


	//�X���b�v�`�F�C���̐���
	hr = factory->CreateSwapChainForHwnd((IUnknown*)queue.lock()->Get(), HWND(window.lock()->Get())
		, &desc, nullptr, nullptr, (IDXGISwapChain1**)swap.GetAddressOf());

	_ASSERT(hr == S_OK);
}

IDXGISwapChain4* SwapChain::Get(void) const
{
	return swap.Get();
}