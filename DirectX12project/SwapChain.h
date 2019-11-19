#pragma once
#include "Obj.h"
#include <memory>
#include <dxgi1_4.h>
#pragma comment(lib, "dxgi.lib")

class Window;
class CommandMng;
class SwapChain :
	public Obj
{
public:
	SwapChain();
	~SwapChain();

	// スワップチェインの取得
	IDXGISwapChain3* Get() const
	{
		return swap;
	}

	// バックバッファの数取得
	unsigned int GetBack() const
	{
		return bufferCnt;
	}
private:
	//ファクトリーの生成
	HRESULT CreateFactory();
	//スワップチェインの生成
	HRESULT CreateSwap();

	IDXGIFactory4* factory;	//ファクトリー
	IDXGISwapChain3* swap;	//スワップチェイン
	unsigned int bufferCnt;			//バックバッファ数

	std::shared_ptr<Window> window;
	std::shared_ptr<CommandMng> command;
};

