#pragma once
#include <wrl.h>
#include <memory>

class Window;
class Queue;
struct IDXGISwapChain4;

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

	// スワップチェイン
	Microsoft::WRL::ComPtr<IDXGISwapChain4>swap;

	//バックバッファ数
	unsigned int bufferCnt;
};

