#pragma once
#include "d3d12.h"

class Window
{
public:
	Window();
	~Window();


	HWND Get(void)
	{
		return handle;
	}

	UINT GetY() const
	{
		return height;
	}

	UINT GetX() const
	{
		return width;
	}
private:
	//ウィンドウプロシージャ
	static LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	void CreateWnd();

	WNDCLASSEX window;
	//ウィンドウサイズ格納用
	RECT rect;
	//ウィンドウハンドル
	HWND handle;

	int height;
	int width;
};

