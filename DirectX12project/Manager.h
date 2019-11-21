#pragma once
#include "Vector3.h"
#include <wrl.h>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>


enum D3D12_PRIMITIVE_TOPOROGY_TYPE : int;
struct ID3D12DescriptorHeap;
struct ID3D12Resource;
class Window;
class Queue;
class Allocator;
class List;
class Fence;
class SwapChain;
class Render;
class RootSignature;
class Pipeline;
class Primitive;

class Manager
{
public:
	~Manager();

	static Manager& Get(void)
	{
		static Manager instance;
		return instance;
	}


private:
	Manager();
	Manager(const Manager&) = delete;
	void operator=(const Manager&) = delete;
};