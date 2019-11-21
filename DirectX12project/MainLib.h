#pragma once
#include "Vector2.h"
#include "Func.h"
#include <string>

namespace create
{
	//������
	bool Init(const Vec2& windowSize, const Vec2& windowPos = 0x8000000, const std::string& parent = "");

	//���b�Z�[�W�m�F
	bool CheckMsg(void);

	// �g���K�[����
	//bool Trigger(const KeyCode& key);

	//�摜�ǂݍ���
	int LoadImg(const std::string& fileName);

	//��ʃN���A
	void Crear(void);

	//�{���̉摜�T�C�Y�ŕ`��
	void DrawImg(const int& id, const Vec2& pos, const float& angle = 0.0f, const bool& turnX = false, const bool& trunY = false, const float& alpha = 1.0f);

	//�`�悵���摜�T�C�Y�ŕ`��
	void DrawImgRect(const int& id, const Vec2& pos, const Vec2& size, const float& angle = 0.0f,
					 const bool& turnX = false, const float& turnY = false, const float& alpha = 1.0f);

	//�w�肵���摜�T�C�Y�Ŏw�肵����`�ɕ������ĕ`��
	void DrawImgDivide(const int& id, const Vec2& pos, const Vec2& size, const Vec2& uvPos, Vec2& uvSize,
				       const float& angle = 0.0f, const bool& turnX = false, const float& trunY = false, const float& alpha = 1.0f);

	//�|�C���g�`��
	void DrawPoint(const Vec2& pos, const float& r, const float& g, const float& b, const float& a = 1.0f);

	//���C���`��
	void DrawLine(const Vec2& pos1, const Vec2& pos2, const float& r, const float& g, const float& b, const float& a = 1.0f);

	//�g���C�A���O���`��
	void DrawTriangle(const Vec2& pos1, const Vec2& pos2, const Vec2& pos3, const float& r, const float& g, const float& b, const float& a = 1.0f);

	//�{�b�N�X�`��
	void DrawBox(const Vec2& pos, const Vec2& size, const float& r, const float& g, const float& b, const float& a = 1.0f);

	//���s
	void Excution(void);

	//�^�[�Q�b�g�ɂ��郉�C�u������ς���
	void ChangeTargetName(const std::string& name);

	//���݃^�[�Q�b�g�ɂ��Ă��郉�C�u�����ʖ����擾
	std::string GetNowTargetName(void);

	//�e�N�X�`���n���h���폜
	void DeleteImg(const int& id);

	//�v���~�e�B�u�f�[�^�폜(���t���[���Ăяo������)
	void DeletePrim(const bool& memReset = false);

	//�摜�f�[�^�폜
	void DeleteImg(const std::string& fileName);
}
