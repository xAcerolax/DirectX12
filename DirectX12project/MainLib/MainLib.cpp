#include "MainLib.h"
#include "../Manager/Manager.h"
#include "../Graphics/Texture/TexLoader.h"
#include <Windows.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxcompiler.lib")

//������
bool create::Init(const Vec2& windowSize, const Vec2& windowPos, const std::string & parent)
{
	return Manager::Get().InitLib(windowSize, windowPos, parent);
}

//���b�Z�[�W�m�F
bool create::CheckMsg(void)
{
	static MSG msg{};

	if (msg.message == WM_QUIT)
	{
		return false;
	}

	//�Ăяo���������L���Ă���E�B���h�E�ɑ��M���ꂽ���b�Z�[�W�ۗ̕�����Ă�����̂��擾
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�ɕϊ�
		TranslateMessage(&msg);
		//�P�̃E�B���h�E�v���V�[�W���Ƀ��b�Z�[�W�𑗏o����
		DispatchMessage(&msg);
	}

	return true;
}

//�摜�ǂݍ���
int create::LoadImg(const std::string& fileName)
{
	return Manager::Get().LoadImg(fileName);
}

//��ʂ̃N���A
void create::Clear(void)
{
	Manager::Get().Clear();
}

//�{���̉摜�T�C�Y�ŕ`��
void create::DrawImg(const int & id, const Vec2& pos, const float & angle, const bool & turnX, const bool & turnY, const float & alpha)
{
	Manager::Get().DrawImg(id, Vec2f(float(pos.x), float(pos.y)), angle, turnX, turnY, alpha);
}

//�w�肵���摜�T�C�Y�ŕ`��
void create::DrawImgRect(const int & id, const Vec2& pos, const Vec2& size, const float & angle, const bool & turnX, const float & turnY, const float & alpha)
{
	Manager::Get().DrawImgRect(id, Vec2f(float(pos.x), float(pos.y)), Vec2f(float(size.x), float(size.y)), angle, turnX, turnY, alpha);
}

//�w�肵���摜�T�C�Y�����w�肵����`�ɕ������ĕ`��
void create::DrawImgDivide(const int& id, const Vec2& pos, const Vec2& size, const Vec2& uvPos, Vec2& uvSize, const float & angle, const bool & turnX, const float & turnY, const float & alpha)
{
	Manager::Get().DrawImgDivide(id, Vec2f(float(pos.x), float(pos.y)), Vec2f(float(size.x), float(size.y))
		, Vec2f(float(uvPos.x), float(uvPos.y)), Vec2f(float(uvSize.x), float(uvSize.y)), angle, turnX, turnY, alpha);
}

//�|�C���g�`��
void create::DrawPoint(const Vec2& pos, const float & r, const float & g, const float & b, const float & a)
{
	Manager::Get().DrawPoint(Vec2f(float(pos.x), float(pos.y)), r, g, b, a);
}

//���C���`��
void create::DrawLine(const Vec2& pos1, const Vec2& pos2, const float & r, const float & g, const float & b, const float & a)
{
	Manager::Get().DrawLine(Vec2f(float(pos1.x), float(pos1.y)), Vec2f(float(pos2.x), float(pos2.y)), r, g, b, a);
}

//�g���C�A���O���`��
void create::DrawTriangle(const Vec2& pos1, const Vec2& pos2, const Vec2& pos3, const float & r, const float & g, const float & b, const float & a)
{
	Manager::Get().DrawTriangle(Vec2f(float(pos1.x), float(pos1.y)), Vec2f(float(pos2.x), float(pos2.y)), Vec2f(float(pos3.x), float(pos3.y)), r, g, b, a);
}

//�{�b�N�X�`��
void create::DrawBox(const Vec2& pos, const Vec2& size, const float & r, const float & g, const float & b, const float & a)
{
	Manager::Get().DrawBox(Vec2f(float(pos.x), float(pos.y)), Vec2f(float(size.x), float(size.y)), r, g, b, a);
}

//���s
void create::Execution(void)
{
	Manager::Get().Execution();
}

//�^�[�Q�b�g�ɂ��郉�C�u������ς���
void create::ChangeTargetName(const std::string & name)
{
	Manager::Get().ChangeTarget(name);
}

//���݃^�[�Q�b�g�ɂ��Ă��郉�C�u�����ʖ����擾
std::string create::GetNowTargetName(void)
{
	return Manager::Get().GetTarget();
}

//�e�N�X�`���n���h���폜
void create::DeleteImg(const int & id)
{
	Manager::Get().DeleteTex(id);
}

//�v���~�e�B�u�f�[�^�폜
void create::DeletePrim(const bool & memReset)
{
	Manager::Get().DeletePrim(memReset);
}

//�摜�f�[�^�폜
void create::DeleteImg(const std::string & fileName)
{
	TexLoader::Get().Delete(fileName);
}
