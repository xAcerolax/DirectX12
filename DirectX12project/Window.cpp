#include "Window.h"
#include <tchar.h>


Window::Window()
{
	CreateWnd();
}


Window::~Window()
{
	//ウィンドウを開放
	UnregisterClass(window.lpszClassName, window.hInstance);
}

LRESULT Window::WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//ウィンドウが破棄されたとき
	if (msg == WM_DESTROY)
	{
		//OSに対してアプリケーション終了を伝える
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void Window::CreateWnd(void)
{
	window.cbClsExtra = 0;								//追加領域
	window.cbWndExtra = 0;								//;;
	window.cbSize = sizeof(WNDCLASSEX);					//WNDCLASSEXのサイズ指定
	window.hbrBackground = CreateSolidBrush(0x000000);  //ウィンドウの背景色を指定
	window.hCursor = LoadCursor(NULL, IDC_ARROW);		//マウスカーソル指定
	window.hIcon = LoadIcon(NULL, IDI_APPLICATION);		//アイコンの指定
	window.hIconSm = LoadIcon(NULL, IDI_APPLICATION);	//アイコンの指定
	window.hInstance = GetModuleHandle(0);				//インスタンスハンドルの指定
	window.lpfnWndProc = (WNDPROC)WindowProcedure;		//ウィンドウプロシージャの指定
	window.lpszClassName = _T("DirectX12");				//ウィンドウの名前を指定
	window.lpszMenuName = _T("DirectX12");				//ウィンドウメニューの名前を指定
	window.style = CS_HREDRAW | CS_VREDRAW;				//ウィンドウの書き直しを指定
	RegisterClassEx(&window);							//ウィンドウの登録

	//ウィンドウサイズ : 縦幅:480 横幅:640
	rect.bottom = 480;
	rect.left = 0;
	rect.right = 640;
	rect.top = 0;

	width = (rect.right - rect.left);
	height = (rect.bottom - rect.top);

	//サイズの補正
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	//ウィンドウ生成
	handle = CreateWindow(window.lpszClassName,
		_T("DirectX12"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(width),
		(height),
		nullptr,
		nullptr,
		window.hInstance,
		nullptr);

}
