#pragma once
#include <wrl.h>

//--------------------------------
//�f�o�C�X�̐���
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

	//�f�o�C�X�̎擾
	ID3D12Device5* Dev(void) const;
private:
	Device();
	Device(const Device&) = delete;
	void operator=(const Device&) = delete;

	// �f�o�C�X����
	void CreateDevice(void);


	// �f�o�C�X
	Microsoft::WRL::ComPtr<ID3D12Device5>device;
};

