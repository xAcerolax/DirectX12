#pragma once
#include "../Single.h"
#include "../Vector/Vector3.h"
#include <wrl.h>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

enum D3D12_PRIMITIVE_TOPOLOGY_TYPE : int;
struct ID3D12DescriptorHeap;
struct ID3D12Resource;
class Window;
class Queue;
class Allocator;
class List;
class Fence;
class SwapChain;
class Render;
class RootSignature;
class Pipeline;
class Texture;
class Primitive;

class MainLib
{
public:
	// �R���X�g���N�^
	MainLib(const Vec2& size, const Vec2& pos, MainLib* parent);
	// �f�X�g���N�^
	~MainLib();

	// ��ʃN���A
	void Clear(void);

	// ���s
	void Execution(void);

	// �`�揀��
	void SetDraw(const size_t& index = 0);

	// �E�B���h�E�T�C�Y�擾
	Vec2 GetWindowSize(void);

	// �R�}���h���X�g�擾
	std::weak_ptr<List>GetList(void) const;

private:
	// �萔���\�[�X����
	void CreateRsc(void);

	// ������
	void Init(void);


	// �E�B���h�E
	std::shared_ptr<Window>window;

	// �L���[
	std::shared_ptr<Queue>queue;

	// �A���P�[�^
	std::vector<std::shared_ptr<Allocator>>allo;

	// ���X�g
	std::shared_ptr<List>list;

	// �t�F���X
	std::shared_ptr<Fence>fence;

	// �X���b�v
	std::shared_ptr<SwapChain>swap;

	// �����_�[
	std::shared_ptr<Render>render;

	// �q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>heap;

	// ���\�[�X
	Microsoft::WRL::ComPtr<ID3D12Resource>rsc;

	// ���M�f�[�^
	Vec2f* data;
};

class Manager :
	public Single<Manager>
{
	friend Single<Manager>;
public:
	// ���C�u����������
	bool InitLib(const Vec2& size, const Vec2& pos, const std::string& parent);

	// �摜�ǂݍ���
	int LoadImg(const std::string& fileName);

	// ��ʃN���A
	void Clear(void);

	// �{���̉摜�T�C�Y�ŕ`��
	void DrawImg(const int& id, const Vec2f& pos, const float& angle, const bool& turnX, const bool& turnY, const float& alpha);

	// �w�肵���摜�T�C�Y�ŕ`��
	void DrawImgRect(const int& id, const Vec2f& pos, const Vec2f& size, const float& angle, const bool& turnX, const bool& turnY, const float& alpha);

	// �w�肵���摜�T�C�Y�Ŏw�肵����`�ɕ������ĕ`��
	void DrawImgDivide(const int& id, const Vec2f& pos, const Vec2f& size, const Vec2f& uvPos, const Vec2f& uvSize,
		const float& angle, const bool& turnX, const bool& turnY, const float& alpha);

	// �|�C���g�`��
	void DrawPoint(const Vec2f& pos, const float& r, const float& g, const float& b, const float& a);

	// ���C���`��
	void DrawLine(const Vec2f& pos1, const Vec2f& pos2, const float& r, const float& g, const float& b, const float& a);

	// �g���C�A���O���`��
	void DrawTriangle(const Vec2f& pos1, const Vec2f& pos2, const Vec2f& pos3, const float& r, const float& g, const float& b, const float& a);

	// �{�b�N�X�`��
	void DrawBox(const Vec2f& pos, const Vec2f& size, const float& r, const float& g, const float& b, const float& a);

	// ���s
	void Execution(void);

	// �e�N�X�`���n���h���̍폜
	void DeleteTex(const int& id);

	// �v���~�e�B�u�f�[�^�̍폜
	void DeletePrim(const bool& memReset);

	// ���C�u�����̃^�[�Q�b�g�؂�ւ�
	void ChangeTarget(const std::string& name);

	// ���C�u�����^�[�Q�b�g�̎擾
	std::string GetTarget(void) const;

private:
	// �R���X�g���N�^
	Manager();
	// �f�X�g���N�^
	~Manager();

	// ���[�g����
	template <typename T>
	void CreateRoot(const std::string& name, const std::initializer_list<T>& fileName, const bool& geoFlag = false);

	// �p�C�v����
	void CreatePipe(const std::string& name, std::weak_ptr<RootSignature>root, const std::initializer_list<unsigned char>& index,
		const D3D12_PRIMITIVE_TOPOLOGY_TYPE& type, const bool& depth = false);

	// ������
	void Init(void);


	// ���C�u�����^�[�Q�b�g
	std::string target;

	// ���[�g
	std::unordered_map<std::string, std::shared_ptr<RootSignature>>root;

	// �p�C�v
	std::unordered_map<std::string, std::shared_ptr<Pipeline>>pipe;

	// �e�N�X�`��
	std::unordered_map<int, std::shared_ptr<Texture>>tex;

	// �v���~�e�B�u
	std::vector<std::shared_ptr<Primitive>>prim;

	// ���C�u����
	std::unordered_map<std::string, std::shared_ptr<MainLib>>lib;
};

