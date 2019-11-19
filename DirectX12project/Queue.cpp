#include "Queue.h"
#include "Device.h"
#include <d3d12.h>
#include <crtdbg.h>

//�R���X�g���N�^
Queue::Queue(const D3D12_COMMAND_LIST_TYPE& type) :
	queue(nullptr)
{
	CreateQueue(type);
}

//�f�X�g���N�^
Queue::~Queue()
{
}

//�R�}���h�L���[����
void Queue::CreateQueue(const D3D12_COMMAND_LIST_TYPE& type)
{
	D3D12_COMMAND_QUEUE_DESC desc{};
	
	desc.Flags = D3D12_COMMAND_QUEUE_FLAGS::D3D12_COMMAND_QUEUE_FLAG_NONE;
	desc.Type  = type;

	auto hr = Device::Get().Dev()->CreateCommandQueue(&desc, IID_PPV_ARGS(&queue));
	_ASSERT(hr == S_OK);
}

//�R�}���h�L���[�擾
ID3D12CommandQueue* Queue::Get(void) const
{
	return queue.Get();
}

