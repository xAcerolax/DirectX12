#pragma once
#include "Vector3.h"
#include <wrl.h>
#include <string>
#include <vector>
#include <memory>

struct ID3D12DescriptorHeap;
struct ID3D12Resource;
class List;

class Texture
{
	// ���_���
	struct Vertex {
		//���W
		Vec3f pos;
		//UV
		Vec2f uv;
	};

	// �萔���
	struct Constant {
		//�摜�T�C�Y
		Vec2f size;
		//���]
		Vec2f reverse;
		//�p�x
		float angle;
		//������
		float alpha;
	};

	// ���\�[�X
	struct Resource {
		//�C���f�b�N�X
		unsigned char index;
		//���\�[�X
		Microsoft::WRL::ComPtr<ID3D12Resource>rsc;

		Resource() : index(0), rsc(nullptr) {}
	};

public:
	// �R���X�g���N�^
	Texture();
	Texture(const std::string& fileName);
	// �f�X�g���N�^
	~Texture();

	// �ǂݍ���
	void Load(const std::string& fileName);

	// �{���̃T�C�Y�ŕ`��
	void DrawImg(const Vec2f& pos, const float& angle, const bool& turnX, const bool& turnY, const float& alpha);

	// �w�肵���T�C�Y�ŕ`��
	void DrawRect(const Vec2f& pos, const Vec2f& size, const float& angle, const bool& turnX, const bool& turnY, const float& alpha);

	// �w�肵���T�C�Y�ŕ����`��
	void DrawDivide(const Vec2f& pos, const Vec2f& size, const Vec2f& uvPos, const Vec2f& uvSize,
		const float& angle, const bool& turnX, const bool& turnY, const float& alpha);

	// �`��
	void Draw(std::weak_ptr<List>list);

private:
	// ������
	void Init(void);

	// ���_���\�[�X����
	void CreateVRsc(void);

	// �萔���\�[�X����
	void CreateCRsc(void);


	// �q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>heap;

	// ���_���\�[�X
	Microsoft::WRL::ComPtr<ID3D12Resource>vRsc;

	// ���_���M�f�[�^
	void* data;

	// �萔���\�[�X
	Resource cRsc;

	// �萔���
	Constant* constant;

	// �C���f�b�N�X
	unsigned char index;

	// ���_���
	std::vector<Vertex>vertex;
};