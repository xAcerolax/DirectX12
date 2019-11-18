#pragma once
#include "Obj.h"

//--------------------------------
//デバイスの生成
//--------------------------------

class Device :
	public Obj
{
public:
	Device();
	~Device();

	//デバイスの取得
	ID3D12Device* Get()const
	{
		return device;
	}
private:
	//デバイスの生成
	HRESULT CreateDevice();


	ID3D12Device* device;
	//機能レベル
	D3D_FEATURE_LEVEL level;
};

