#pragma once
#include "d3d12.h"

//‰ğ•úƒ}ƒNƒ
#define Release(X) {if ((X) != nullptr) (X)->Release(); (X) = nullptr;}


class Obj
{
public:
	Obj() : result(S_OK){
	};
	virtual ~Obj(){
	};

protected:
	//QÆŒ‹‰Ê
	HRESULT result;
};

