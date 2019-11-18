#include "CommandMng.h"
#include "Device.h"


CommandMng::CommandMng() :
	queue(nullptr), allocator(nullptr), list(nullptr)
{
	device = std::make_shared<Device>();
	CreateQueue();
	CreateAllocator();
	CreateList();
}

CommandMng::~CommandMng()
{
	Release(queue);
	Release(list);
	Release(allocator);
}

//コマンドキュー生成
HRESULT CommandMng::CreateQueue()
{
	D3D12_COMMAND_QUEUE_DESC desc;
	desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	desc.NodeMask = 0;
	desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	
	//コマンドキュー生成
	result = device->Get()->CreateCommandQueue(&desc, IID_PPV_ARGS(&queue));

	return result;
}

//コマンドアロケータの生成
HRESULT CommandMng::CreateAllocator()
{
	result = device->Get()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT
												 , IID_PPV_ARGS(&allocator));

	return result;
}

//コマンドリストの生成
HRESULT CommandMng::CreateList()
{
	result = device->Get()->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT,
											  allocator, nullptr, IID_PPV_ARGS(&list));

	//コマンドリストを一時的にクローズ
	list->Close();

	return result;
}
