#include "Allocator.h"
#include "../Device/Device.h"
#include <d3d12.h>
#include <crtdbg.h>


Allocator::Allocator(const D3D12_COMMAND_LIST_TYPE& type) :
	allo(nullptr)
{
	CreateAllo(type);
}

Allocator::~Allocator()
{
}

void Allocator::CreateAllo(const D3D12_COMMAND_LIST_TYPE& type)
{
	auto hr = Device::Get().Dev()->CreateCommandAllocator(type, IID_PPV_ARGS(&allo));
	_ASSERT(hr == S_OK);
}

ID3D12CommandAllocator* Allocator::Get(void) const
{
	return allo.Get();
}
