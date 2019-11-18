#include "Window.h"
#include "SwapChain.h"
#include <memory>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	std::shared_ptr<Window> window;
	window = std::make_shared<Window>();


	ShowWindow(window->Get(), SW_SHOW);
	MSG msg = {};

	while (msg.message != WM_QUIT)
	{
		//呼び出し側スレッドが所有しているウィンドウに送信されたメッセージの保留されている物を取得
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			//仮想キーメッセージを文字メッセージに変換
			TranslateMessage(&msg);
			//1つのウィドウプロシージャにメッセージを送出する
			DispatchMessage(&msg);
		}
	}

	return 0;
}