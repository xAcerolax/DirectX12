#pragma once
#include "d3d12.h"

//解放マクロ
#define Release(X) {if ((X) != nullptr) (X)->Release(); (X) = nullptr;}


class Obj
{
public:
	Obj() : result(S_OK){
	};
	virtual ~Obj(){
	};

protected:
	//参照結果
	HRESULT result;
};

