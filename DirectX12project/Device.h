#pragma once
#include "Obj.h"

//--------------------------------
//�f�o�C�X�̐���
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

	//�f�o�C�X�̎擾
	ID3D12Device* Dev()const
	{
		return device;
	}
private:
	Device();
	Device(const Device&) = delete;
	void operator=(const Device&) = delete;

	//�f�o�C�X�̐���
	HRESULT CreateDevice();


	ID3D12Device* device;
	//�@�\���x��
	D3D_FEATURE_LEVEL level;
};

