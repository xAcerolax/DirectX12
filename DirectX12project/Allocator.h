#pragma once
#include <wrl.h>

enum D3D12_COMMAND_LIST_TYPE : int;
struct ID3D12CommandAllocator;

class Allocator
{
public:
	//�R���X�g���N�^
	Allocator(const D3D12_COMMAND_LIST_TYPE& type);
	//�f�X�g���N�^
	~Allocator();

	//�R�}���h�A���P�[�^�擾
	ID3D12CommandAllocator* Get(void) const;
private:
	// �R�}���h�A���P�[�^����
	void CreateAllo(const D3D12_COMMAND_LIST_TYPE& type);

	// �R�}���h�A���P�[�^
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator>allo;
};

