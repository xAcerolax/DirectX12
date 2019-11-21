#pragma once
#include "Vector2.h"
#include "Func.h"
#include <string>

namespace create
{
	//初期化
	bool Init(const Vec2& windowSize, const Vec2& windowPos = 0x8000000, const std::string& parent = "");

	//メッセージ確認
	bool CheckMsg(void);

	// トリガー入力
	//bool Trigger(const KeyCode& key);

	//画像読み込み
	int LoadImg(const std::string& fileName);

	//画面クリア
	void Crear(void);

	//本来の画像サイズで描画
	void DrawImg(const int& id, const Vec2& pos, const float& angle = 0.0f, const bool& turnX = false, const bool& trunY = false, const float& alpha = 1.0f);

	//描画した画像サイズで描画
	void DrawImgRect(const int& id, const Vec2& pos, const Vec2& size, const float& angle = 0.0f,
					 const bool& turnX = false, const float& turnY = false, const float& alpha = 1.0f);

	//指定した画像サイズで指定した矩形に分割して描画
	void DrawImgDivide(const int& id, const Vec2& pos, const Vec2& size, const Vec2& uvPos, Vec2& uvSize,
				       const float& angle = 0.0f, const bool& turnX = false, const float& trunY = false, const float& alpha = 1.0f);

	//ポイント描画
	void DrawPoint(const Vec2& pos, const float& r, const float& g, const float& b, const float& a = 1.0f);

	//ライン描画
	void DrawLine(const Vec2& pos1, const Vec2& pos2, const float& r, const float& g, const float& b, const float& a = 1.0f);

	//トライアングル描画
	void DrawTriangle(const Vec2& pos1, const Vec2& pos2, const Vec2& pos3, const float& r, const float& g, const float& b, const float& a = 1.0f);

	//ボックス描画
	void DrawBox(const Vec2& pos, const Vec2& size, const float& r, const float& g, const float& b, const float& a = 1.0f);

	//実行
	void Excution(void);

	//ターゲットにするライブラリを変える
	void ChangeTargetName(const std::string& name);

	//現在ターゲットにしているライブラリ個別名を取得
	std::string GetNowTargetName(void);

	//テクスチャハンドル削除
	void DeleteImg(const int& id);

	//プリミティブデータ削除(毎フレーム呼び出し推奨)
	void DeletePrim(const bool& memReset = false);

	//画像データ削除
	void DeleteImg(const std::string& fileName);
}
