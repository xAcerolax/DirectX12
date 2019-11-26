#pragma once
#include <wrl.h>
#include <memory>

struct ID3D12Fence;
class Queue;

class Fence
{
public:
	// �R���X�g���N�^
	Fence(std::weak_ptr<Queue>queue);
	// �f�X�g���N�^
	~Fence();

	// �ҋ@
	void Wait(void);


private:
	// �t�F���X����
	void CreateFence(void);


	// �L���[
	std::weak_ptr<Queue>queue;
	// �t�F���X
	Microsoft::WRL::ComPtr<ID3D12Fence>fence;	


	// �C�x���g�n���h��
	void* handle;
	// �J�E���g
	unsigned __int64 cnt;						
};