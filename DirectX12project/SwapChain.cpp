#include "SwapChain.h"
#include "Window.h"
#include "CommandMng.h"


SwapChain::SwapChain()
{
	CreateFactory();
	CreateSwap();
}

SwapChain::~SwapChain()
{
	Release(swap);
	Release(factory);
}

HRESULT SwapChain::CreateFactory()
{
	result = CreateDXGIFactory1(IID_PPV_ARGS(&factory));
	return result;
}

HRESULT SwapChain::CreateSwap()
{
	window = std::make_shared<Window>();
	command = std::make_shared<CommandMng>();

	//スワップチェイン設定用構造体
	DXGI_SWAP_CHAIN_DESC1 desc = {};
	desc.AlphaMode		= DXGI_ALPHA_MODE_UNSPECIFIED;
	desc.BufferCount	= 2;
	desc.BufferUsage	= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.Flags			= 0;
	desc.Format			= DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.Height			= window->GetY();
	desc.Width			= window->GetY();
	desc.SampleDesc		= { 1,0 };
	desc.Scaling		= DXGI_SCALING_STRETCH;
	desc.Stereo			= false;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;


	//スワップチェインの生成
	result = factory->CreateSwapChainForHwnd(command->Get(), window->Get(), &desc,
											 nullptr, nullptr, (IDXGISwapChain1**)(&swap));
	//バックバッファ数保存
	bufferCnt = desc.BufferCount;

	return result;
}
