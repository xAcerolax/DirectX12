#pragma once
#include <wrl.h>
#include <memory>

struct IDXGISwapChain4;
class Window;
class Queue;


class SwapChain 
{
public:
	//コンストラクタ
	SwapChain(std::weak_ptr<Window>window, std::weak_ptr<Queue>queue);
	//デストラクタ
	~SwapChain();


	// スワップチェインの取得
	IDXGISwapChain4* Get(void) const;

	// バックバッファの数取得
	unsigned int GetBack() const
	{
		return bufferCnt;
	}


private:
	// スワップチェインの生成
	void CreateSwap(void);
	
	std::weak_ptr<Window> window;					//ウィンドウ
	std::weak_ptr<Queue> queue;						//キュー
	Microsoft::WRL::ComPtr<IDXGISwapChain4>swap;	// スワップチェイン

	//バックバッファ数
	unsigned int bufferCnt;
};

