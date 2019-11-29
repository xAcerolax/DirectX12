#pragma once
#include "../../Single.h"
#include <wrl.h>

//--------------------------------
//デバイスの生成
//--------------------------------

struct ID3D12Device;
struct IDXGIFactory1;

class Device :
	public Single<Device>
{
	friend Single<Device>;
public:
	

	//static Device& Get(void)
	//{
	//	static Device instance;
	//	return instance;
	//}

	//デバイスの取得
	ID3D12Device* Dev(void) const;


private:
	//コンストラクタ
	Device();
	//デストラクタ
	~Device();

	/*Device(const Device&) = delete;
	void operator=(const Device&) = delete;*/

	// デバイス生成
	void CreateDevice(void);


	// デバイス
	Microsoft::WRL::ComPtr<ID3D12Device>device;
};

