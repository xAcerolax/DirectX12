#pragma once
#include "Obj.h"

//--------------------------------
//�f�o�C�X�̐���
//--------------------------------

class Device :
	public Obj
{
public:
	Device();
	~Device();

	//�f�o�C�X�̎擾
	ID3D12Device* Get()const
	{
		return device;
	}
private:
	//�f�o�C�X�̐���
	HRESULT CreateDevice();


	ID3D12Device* device;
	//�@�\���x��
	D3D_FEATURE_LEVEL level;
};

