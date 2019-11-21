#pragma once
#include <wrl.h>

//--------------------------------
//デバイスの生成
//--------------------------------

struct ID3D12Device5;
struct IDXGIFactory1;

class Device
{
public:
	~Device();

	static Device& Get(void)
	{
		static Device instance;
		return instance;
	}

	//デバイスの取得
	ID3D12Device5* Dev(void) const;
private:
	Device();
	Device(const Device&) = delete;
	void operator=(const Device&) = delete;

	// デバイス生成
	void CreateDevice(void);


	// デバイス
	Microsoft::WRL::ComPtr<ID3D12Device5>device;
};

