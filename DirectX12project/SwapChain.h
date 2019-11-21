#pragma once
#include <wrl.h>
#include <memory>

class Window;
class Queue;
struct IDXGISwapChain4;

class SwapChain 
{
public:
	//�R���X�g���N�^
	SwapChain(std::weak_ptr<Window>window, std::weak_ptr<Queue>queue);
	//�f�X�g���N�^
	~SwapChain();


	// �X���b�v�`�F�C���̎擾
	IDXGISwapChain4* Get(void) const;

	// �o�b�N�o�b�t�@�̐��擾
	unsigned int GetBack() const
	{
		return bufferCnt;
	}


private:
	// �X���b�v�`�F�C���̐���
	void CreateSwap(void);
	
	std::weak_ptr<Window> window;					//�E�B���h�E
	std::weak_ptr<Queue> queue;						//�L���[

	// �X���b�v�`�F�C��
	Microsoft::WRL::ComPtr<IDXGISwapChain4>swap;

	//�o�b�N�o�b�t�@��
	unsigned int bufferCnt;
};

