#include "MainLib.h"
#include "../Manager/Manager.h"
#include "../Graphics/Texture/TexLoader.h"
#include <Windows.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxcompiler.lib")

//初期化
bool create::Init(const Vec2& windowSize, const Vec2& windowPos, const std::string & parent)
{
	return Manager::Get().InitLib(windowSize, windowPos, parent);
}

//メッセージ確認
bool create::CheckMsg(void)
{
	static MSG msg{};

	if (msg.message == WM_QUIT)
	{
		return false;
	}

	//呼び出し側が所有しているウィンドウに送信されたメッセージの保留されているものを取得
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		//仮想キーメッセージを文字メッセージに変換
		TranslateMessage(&msg);
		//１つのウィンドウプロシージャにメッセージを送出する
		DispatchMessage(&msg);
	}

	return true;
}

//画像読み込み
int create::LoadImg(const std::string& fileName)
{
	return Manager::Get().LoadImg(fileName);
}

//画面のクリア
void create::Clear(void)
{
	Manager::Get().Clear();
}

//本来の画像サイズで描画
void create::DrawImg(const int & id, const Vec2& pos, const float & angle, const bool & turnX, const bool & turnY, const float & alpha)
{
	Manager::Get().DrawImg(id, Vec2f(float(pos.x), float(pos.y)), angle, turnX, turnY, alpha);
}

//指定した画像サイズで描画
void create::DrawImgRect(const int & id, const Vec2& pos, const Vec2& size, const float & angle, const bool & turnX, const float & turnY, const float & alpha)
{
	Manager::Get().DrawImgRect(id, Vec2f(float(pos.x), float(pos.y)), Vec2f(float(size.x), float(size.y)), angle, turnX, turnY, alpha);
}

//指定した画像サイズｄえ指定した矩形に分割して描画
void create::DrawImgDivide(const int& id, const Vec2& pos, const Vec2& size, const Vec2& uvPos, Vec2& uvSize, const float & angle, const bool & turnX, const float & turnY, const float & alpha)
{
	Manager::Get().DrawImgDivide(id, Vec2f(float(pos.x), float(pos.y)), Vec2f(float(size.x), float(size.y))
		, Vec2f(float(uvPos.x), float(uvPos.y)), Vec2f(float(uvSize.x), float(uvSize.y)), angle, turnX, turnY, alpha);
}

//ポイント描画
void create::DrawPoint(const Vec2& pos, const float & r, const float & g, const float & b, const float & a)
{
	Manager::Get().DrawPoint(Vec2f(float(pos.x), float(pos.y)), r, g, b, a);
}

//ライン描画
void create::DrawLine(const Vec2& pos1, const Vec2& pos2, const float & r, const float & g, const float & b, const float & a)
{
	Manager::Get().DrawLine(Vec2f(float(pos1.x), float(pos1.y)), Vec2f(float(pos2.x), float(pos2.y)), r, g, b, a);
}

//トライアングル描画
void create::DrawTriangle(const Vec2& pos1, const Vec2& pos2, const Vec2& pos3, const float & r, const float & g, const float & b, const float & a)
{
	Manager::Get().DrawTriangle(Vec2f(float(pos1.x), float(pos1.y)), Vec2f(float(pos2.x), float(pos2.y)), Vec2f(float(pos3.x), float(pos3.y)), r, g, b, a);
}

//ボックス描画
void create::DrawBox(const Vec2& pos, const Vec2& size, const float & r, const float & g, const float & b, const float & a)
{
	Manager::Get().DrawBox(Vec2f(float(pos.x), float(pos.y)), Vec2f(float(size.x), float(size.y)), r, g, b, a);
}

//実行
void create::Execution(void)
{
	Manager::Get().Execution();
}

//ターゲットにするライブラリを変える
void create::ChangeTargetName(const std::string & name)
{
	Manager::Get().ChangeTarget(name);
}

//現在ターゲットにしているライブラリ個別名を取得
std::string create::GetNowTargetName(void)
{
	return Manager::Get().GetTarget();
}

//テクスチャハンドル削除
void create::DeleteImg(const int & id)
{
	Manager::Get().DeleteTex(id);
}

//プリミティブデータ削除
void create::DeletePrim(const bool & memReset)
{
	Manager::Get().DeletePrim(memReset);
}

//画像データ削除
void create::DeleteImg(const std::string & fileName)
{
	TexLoader::Get().Delete(fileName);
}
