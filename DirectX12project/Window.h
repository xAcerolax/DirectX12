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
private:
	//�E�B���h�E�v���V�[�W��
	static LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	void CreateWnd();

	WNDCLASSEX window;
	//�E�B���h�E�T�C�Y�i�[�p
	RECT rect;
	//�E�B���h�E�n���h��
	HWND handle;

	int height;
	int width;
};

