#pragma once
#include "Obj.h"
#include <memory>

class Device;
class Command :
	public Obj
{
public:
	Command();
	virtual ~Command();

protected:
	std::shared_ptr<Device> device;
};

