#pragma once
#include "Vector2.h"
#include <wrl.h>
#include <memory>

enum D3D12_COMMAND_LIST_TYPE : int;
enum D3D12_RESOURCE_STATES : int;
struct ID3D12GraphicsCommandList5;
struct ID3D12DescriptorHeap;
struct ID3D12Resource;
class Allocator;

class List
{
public:
	//�R���X�g���N�^
	List(std::weak_ptr<Allocator>allo, const D3D12_COMMAND_LIST_TYPE& type);
	//�f�X�g���N�^
	~List();


	//�r���[�|�[�g�Z�b�g
	void ViewPort(const Vec2& size);

	//�V�U�[�Z�b�g
	void Scissor(const Vec2& size);

	//�o���A�Z�b�g
	void Barrier(ID3D12Resource* rsc, const D3D12_RESOURCE_STATES& before, const D3D12_RESOURCE_STATES& after);

	//UAV�o���A�Z�b�g
	void Barrier(ID3D12Resource* rsc);

	//�O���t�B�b�N���[�g�e�[�u���Z�b�g
	void SetGraphicsTable(const unsigned int& id, ID3D12DescriptorHeap* heap, const size_t& index = 0);

	//�R���s���[�g���[�g�e�[�u���Z�b�g
	void SetComputeTable(const unsigned int& id, ID3D12DescriptorHeap* heap, const size_t& index = 0);

	// �R�}���h���X�g�擾
	ID3D12GraphicsCommandList5* Get(void) const;

private:
	//�R�}���h���X�g����
	void CreateList(const D3D12_COMMAND_LIST_TYPE& type);


	//�A���P�[�^
	std::weak_ptr<Allocator>allo;
	//�R�}���h���X�g
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList5>list;
};

