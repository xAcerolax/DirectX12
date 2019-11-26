#pragma once
#include <wrl.h>

enum D3D12_COMMAND_LIST_TYPE : int;
struct ID3D12CommandQueue;

class Queue
{
public:
	//�R���X�g���N�^
	Queue(const D3D12_COMMAND_LIST_TYPE& type);
	//�f�X�g���N�^
	~Queue();

	//�R�}���h�L���[�擾
	ID3D12CommandQueue* Get(void) const;
private:
	//�R�}���h�L���[����
	void CreateQueue(const D3D12_COMMAND_LIST_TYPE& type);

	//�R�}���h�L���[
	Microsoft::WRL::ComPtr<ID3D12CommandQueue>queue;
};

