#pragma once
#include "Obj.h"

//--------------------------------
//デバイスの生成
//--------------------------------

class Device :
	public Obj
{
public:
	
	~Device();

	static Device& Get()
	{
		static Device instance;
		return instance;
	}

	//デバイスの取得
	ID3D12Device* Dev()const
	{
		return device;
	}
private:
	Device();
	Device(const Device&) = delete;
	void operator=(const Device&) = delete;

	//デバイスの生成
	HRESULT CreateDevice();


	ID3D12Device* device;
	//機能レベル
	D3D_FEATURE_LEVEL level;
};

