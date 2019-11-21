#include "MainLib.h"


#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxcompiler.lib")

//èâä˙âª
bool create::Init(const Vec2& windowSize, const Vec2& windowPos, const std::string & parent)
{
	return false;
}

bool create::CheckMsg(void)
{
	return false;
}

void create::Crear(void)
{
}

void create::DrawImg(const int & id, const Vec2& pos, const float & angle, const bool & turnX, const bool & trunY, const float & alpha)
{
}

void create::DrawImgRect(const int & id, const Vec2& pos, const Vec2& size, const float & angle, const bool & turnX, const float & turnY, const float & alpha)
{
}

void create::DrawImgDivide(const int& id, const Vec2& pos, const Vec2& size, const Vec2& uvPos, Vec2& uvSize, const float & angle, const bool & turnX, const float & trunY, const float & alpha)
{
}

void create::DrawPoint(const Vec2& pos, const float & r, const float & g, const float & b, const float & a)
{
}

void create::DrawLine(const Vec2& pos1, const Vec2& pos2, const float & r, const float & g, const float & b, const float & a)
{
}

void create::DrawTriangle(const Vec2& pos1, const Vec2& pos2, const Vec2& pos3, const float & r, const float & g, const float & b, const float & a)
{
}

void create::DrawBox(const Vec2& pos, const Vec2& size, const float & r, const float & g, const float & b, const float & a)
{
}

void create::Excution(void)
{
}

void create::ChangeTargetName(const std::string & name)
{
}

std::string create::GetNowTargetName(void)
{
	return std::string();
}

void create::DeleteImg(const int & id)
{
}

void create::DeletePrim(const bool & memReset)
{
}

void create::DeleteImg(const std::string & fileName)
{
}
