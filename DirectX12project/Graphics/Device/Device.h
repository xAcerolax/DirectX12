#pragma once
#include "../../Single.h"
#include <wrl.h>

//--------------------------------
//�f�o�C�X�̐���
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

	//�f�o�C�X�̎擾
	ID3D12Device* Dev(void) const;


private:
	//�R���X�g���N�^
	Device();
	//�f�X�g���N�^
	~Device();

	/*Device(const Device&) = delete;
	void operator=(const Device&) = delete;*/

	// �f�o�C�X����
	void CreateDevice(void);


	// �f�o�C�X
	Microsoft::WRL::ComPtr<ID3D12Device>device;
};

