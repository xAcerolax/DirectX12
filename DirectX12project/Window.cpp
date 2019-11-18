#include "Window.h"
#include <tchar.h>


Window::Window()
{
	CreateWnd();
}


Window::~Window()
{
	//�E�B���h�E���J��
	UnregisterClass(window.lpszClassName, window.hInstance);
}

LRESULT Window::WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//�E�B���h�E���j�����ꂽ�Ƃ�
	if (msg == WM_DESTROY)
	{
		//OS�ɑ΂��ăA�v���P�[�V�����I����`����
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void Window::CreateWnd(void)
{
	window.cbClsExtra = 0;								//�ǉ��̈�
	window.cbWndExtra = 0;								//;;
	window.cbSize = sizeof(WNDCLASSEX);					//WNDCLASSEX�̃T�C�Y�w��
	window.hbrBackground = CreateSolidBrush(0x000000);  //�E�B���h�E�̔w�i�F���w��
	window.hCursor = LoadCursor(NULL, IDC_ARROW);		//�}�E�X�J�[�\���w��
	window.hIcon = LoadIcon(NULL, IDI_APPLICATION);		//�A�C�R���̎w��
	window.hIconSm = LoadIcon(NULL, IDI_APPLICATION);	//�A�C�R���̎w��
	window.hInstance = GetModuleHandle(0);				//�C���X�^���X�n���h���̎w��
	window.lpfnWndProc = (WNDPROC)WindowProcedure;		//�E�B���h�E�v���V�[�W���̎w��
	window.lpszClassName = _T("DirectX12");				//�E�B���h�E�̖��O���w��
	window.lpszMenuName = _T("DirectX12");				//�E�B���h�E���j���[�̖��O���w��
	window.style = CS_HREDRAW | CS_VREDRAW;				//�E�B���h�E�̏����������w��
	RegisterClassEx(&window);							//�E�B���h�E�̓o�^

	//�E�B���h�E�T�C�Y : �c��:480 ����:640
	rect.bottom = 480;
	rect.left = 0;
	rect.right = 640;
	rect.top = 0;

	width = (rect.right - rect.left);
	height = (rect.bottom - rect.top);

	//�T�C�Y�̕␳
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	//�E�B���h�E����
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
