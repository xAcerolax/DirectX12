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

	// �X���b�v�`�F�C���̎擾
	IDXGISwapChain3* Get() const
	{
		return swap;
	}

	// �o�b�N�o�b�t�@�̐��擾
	unsigned int GetBack() const
	{
		return bufferCnt;
	}
private:
	//�t�@�N�g���[�̐���
	HRESULT CreateFactory();
	//�X���b�v�`�F�C���̐���
	HRESULT CreateSwap();

	IDXGIFactory4* factory;	//�t�@�N�g���[
	IDXGISwapChain3* swap;	//�X���b�v�`�F�C��
	unsigned int bufferCnt;			//�o�b�N�o�b�t�@��

	std::shared_ptr<Window> window;
	std::shared_ptr<CommandMng> command;
};

