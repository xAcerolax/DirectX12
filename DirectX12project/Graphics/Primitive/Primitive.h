#pragma once
#include "../../Vector/Vector3.h"
#include <wrl.h>
#include <vector>
#include <memory>

struct ID3D12DescriptorHeap;
struct ID3D12Resource;
class List;


namespace create
{
	// �v���~�e�B�u
	enum class PrimType 
	{
		POINT = 1,
		LINE = 2,
		TRIANGLE = 3,
		BOX = 4
	};

	// �F���
	struct Color {
		float r;
		float g;
		float b;
		float a;

		Color() {
			r = g = b = a = 0.0f;
		}
		Color(const float& r, const float& g, const float& b, const float& a) :
			r(r), g(g), b(b), a(a) {}
	};
}

class Primitive
{
public:
	// �R���X�g���N�^
	Primitive(std::weak_ptr<List>list, const create::PrimType& type);
	// �f�X�g���N�^
	~Primitive();

	// �|�C���g�`��
	void DrawPoint(const Vec2f& pos, const create::Color& color);

	// ���C���`��
	void DrawLine(const Vec2f& pos1, const Vec2f& pos2, const create::Color& color);

	// �g���C�A���O���`��
	void DrawTriangle(const Vec2f& pos1, const Vec2f& pos2, const Vec2f& pos3, const create::Color& color);

	// �{�b�N�X�`��
	void DrawBox(const Vec2f& pos, const Vec2f& size, const create::Color& color);

	// �`��
	void Draw(void);


private:
	// ���_���\�[�X����
	void CreateVRsc(void);

	// �萔���\�[�X����
	void CreateCRsc(void);

	// ������
	void Init(void);


	// ���X�g
	std::weak_ptr<List> list;

	// �q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> heap;

	// ���_���\�[�X
	Microsoft::WRL::ComPtr<ID3D12Resource> vRsc;

	// �萔���\�[�X
	Microsoft::WRL::ComPtr<ID3D12Resource> cRsc;

	// �F���
	create::Color* color;

	// ���_
	std::vector<Vec3f>vertex;
};