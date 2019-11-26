#include "Func.h"
#include <vector>
#include <random>
#include <Windows.h>


// �}���`�o�C�g���������j�R�[�h�����ɕϊ�
std::wstring create::ChangeCode(const std::string& code)
{
	std::vector<wchar_t>buf(MultiByteToWideChar(CP_ACP, 0, code.c_str(), -1, nullptr, 0));
	MultiByteToWideChar(CP_ACP, 0, code.c_str(), -1, &buf.front(), int(buf.size()));

	return std::wstring(buf.begin(), buf.end());
}


// ���j�R�[�h�������}���`�o�C�g�����ɕϊ�
std::string create::ChangeCode(const std::wstring& code)
{
	//�T�C�Y�̎擾
	auto byteSize = WideCharToMultiByte(CP_ACP, 0, code.c_str(), -1, nullptr, 0, nullptr, nullptr);

	std::string str;
	str.resize(byteSize);

	//�ϊ�
	byteSize = WideCharToMultiByte(CP_ACP, 0, code.c_str(), static_cast<int>(code.size()), &str[0], byteSize, nullptr, nullptr);

	return str;
}

// �~����
float create::PI(void)
{
	return 3.14159265f;
}

// ���W�A���p�x�ϊ�
template <typename T>
T create::Rad(const T& angle)
{
	return T(angle * PI() / 180.0f);
}
template float create::Rad(const float&);
template double create::Rad(const double&);


// �ʓx�@�p�x�ϊ�
template<typename T>
T create::Angle(const T& rad)
{
	return T(rad * 180.0f * PI());
}
template float create::Angle(const float&);
template double create::Angle(const double&);


// �����_��
int create::Random(const int& min, const int& max)
{
	std::random_device dev;
#ifdef _WIN64
	std::mt19937_64 mt(dev());
#else
	std::mt19937 mt(dev());
#endif
	std::uniform_int_distribution<int>dist(min, max);

	return dist(mt);
}


// �����_��
template <typename T>
T create::Random(const T& min, const T& max)
{
	std::random_device dev;
#ifdef _WIN64
	std::mt19937_64 mt(dev());
#else
	std::mt19937 mt(dev());
#endif
	std::uniform_real_distribution<T>dist(min, max);

	return dist(mt);
}

template float create::Random(const float&, const float&);
template double create::Random(const double&, const double&);