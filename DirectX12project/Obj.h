#pragma once
#include "d3d12.h"

//����}�N��
#define Release(X) {if ((X) != nullptr) (X)->Release(); (X) = nullptr;}


class Obj
{
public:
	Obj() : result(S_OK){
	};
	virtual ~Obj(){
	};

protected:
	//�Q�ƌ���
	HRESULT result;
};

