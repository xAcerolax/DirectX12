#pragma once
#include "Command.h"

//--------------------------------
//コマンド周り
//コマンドキュー,アロケータ,リストの生成と取得
//--------------------------------
class CommandMng :
	public Command
{
public:
	CommandMng();
	~CommandMng();

	// コマンドキューの取得
	ID3D12CommandQueue* Get() const
	{
		return queue;
	}
	//コマンドアロケータ取得
	ID3D12CommandAllocator* GetAllocator() const
	{
		return allocator;
	}

	//コマンドリスト取得
	ID3D12GraphicsCommandList* GetList() const
	{
		return list;
	}
private:
	//コマンドキューの生成
	HRESULT CreateQueue();
	//コマンドアロケータ生成
	HRESULT CreateAllocator();
	//コマンドリスト生成
	HRESULT CreateList();

	ID3D12CommandQueue* queue;
	ID3D12CommandAllocator* allocator;
	ID3D12GraphicsCommandList* list;
};

