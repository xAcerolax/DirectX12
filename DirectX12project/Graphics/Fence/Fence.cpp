#include "Fence.h"
#include "../Device/Device.h"
#include "../Queue/Queue.h"
#include <d3d12.h>
#include <crtdbg.h>

// �R���X�g���N�^
Fence::Fence(std::weak_ptr<Queue> queue) :
	queue(queue), fence(nullptr), handle(CreateEventEx(nullptr, false, false, EVENT_ALL_ACCESS)), cnt(0)
{
	CreateFence();
}

// �f�X�g���N�^
Fence::~Fence()
{
	CloseHandle(handle);
}

// �t�F���X����
void Fence::CreateFence(void)
{
	auto hr = Device::Get().Dev()->CreateFence(cnt, D3D12_FENCE_FLAGS::D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
	_ASSERT(hr == S_OK);

	cnt = 1;
}

// �ҋ@
void Fence::Wait(void)
{
	++cnt;
	auto hr = queue.lock()->Get()->Signal(fence.Get(), cnt);
	_ASSERT(hr == S_OK);

	while (fence->GetCompletedValue() != cnt)
	{
		hr = fence->SetEventOnCompletion(cnt, handle);
		_ASSERT(hr == S_OK);

		WaitForSingleObject(handle, INFINITE);
	}
}