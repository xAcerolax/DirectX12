#pragma once
#include "Command.h"

//--------------------------------
//�R�}���h����
//�R�}���h�L���[,�A���P�[�^,���X�g�̐����Ǝ擾
//--------------------------------
class CommandMng :
	public Command
{
public:
	CommandMng();
	~CommandMng();

	// �R�}���h�L���[�̎擾
	ID3D12CommandQueue* Get() const
	{
		return queue;
	}
	//�R�}���h�A���P�[�^�擾
	ID3D12CommandAllocator* GetAllocator() const
	{
		return allocator;
	}

	//�R�}���h���X�g�擾
	ID3D12GraphicsCommandList* GetList() const
	{
		return list;
	}
private:
	//�R�}���h�L���[�̐���
	HRESULT CreateQueue();
	//�R�}���h�A���P�[�^����
	HRESULT CreateAllocator();
	//�R�}���h���X�g����
	HRESULT CreateList();

	ID3D12CommandQueue* queue;
	ID3D12CommandAllocator* allocator;
	ID3D12GraphicsCommandList* list;
};

