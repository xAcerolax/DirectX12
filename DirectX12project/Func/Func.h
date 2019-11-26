#pragma once
#include <string>


namespace create
{
	// �}���`�o�C�g���������j�R�[�h�����ɕϊ�
	std::wstring ChangeCode(const std::string& code);

	// ���j�R�[�h�������}���`�o�C�g�����ɕϊ�
	std::string ChangeCode(const std::wstring& code);

	// �~����
	float PI(void);

	// ���W�A���p�x�ϊ�
	template <typename T>
	T Rad(const T& angle);

	// �ʓx�@�p�x�ϊ�
	template <typename T>
	T Angle(const T& rad);

	// �����_��
	int Random(const int& min, const int& max);

	// �����_��
	template <typename T>
	T Random(const T& min, const T& max);
}