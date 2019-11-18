#include "Device.h"
#include <d3d12.h>
#pragma comment(lib, "d3d12.lib")


//�@�\���x��
D3D_FEATURE_LEVEL levels[] =
{
	D3D_FEATURE_LEVEL_12_1,
	D3D_FEATURE_LEVEL_12_0,
	D3D_FEATURE_LEVEL_11_1,
	D3D_FEATURE_LEVEL_11_0
};


Device::Device() : 
	device(nullptr)
{
	CreateDevice();
}


Device::~Device()
{
	Release(device);
}

//�f�o�C�X�̐���
HRESULT Device::CreateDevice()
{
	for (auto& i : levels)
	{
		result = D3D12CreateDevice(nullptr, i, IID_PPV_ARGS(&device));
		if (result == S_OK)
		{
			//���x���̊i�[
			level = i;
			break;
		}
	}
	return result;
}
