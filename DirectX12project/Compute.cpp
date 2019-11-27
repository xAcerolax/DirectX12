#include "Compute.h"
#include "Graphics/Queue/Queue.h"
#include "Graphics/Allocator/Allocator.h"
#include "Graphics/List/List.h"
#include "Graphics/Fence/Fence.h"
#include "Graphics/RootSignature/RootSignature.h"
#include "Graphics/Pipeline/Pipeline.h"
#include "Graphics/Descriptor/Descriptor.h"
#include <d3d12.h>


//�R���X�g���N�^
Compute::Compute() :
	heap(nullptr), index(0)
{
	queue = std::make_shared<Queue>(D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_COMPUTE);
	allo = std::make_shared<Allocator>(D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_COMPUTE);
	list = std::make_shared<List>(allo, D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_COMPUTE);
	fence = std::make_shared<Fence>(queue);
}

//�f�X�g���N�^
Compute::~Compute()
{
}


//�V�F�[�_�R���p�C���ǂݍ���
void Compute::Compile(const std::string& fileName, const std::string& func, const std::string& ver)
{
	root = std::make_shared<RootSignature>();
	root->Compute(fileName, func, ver);
	pipe = std::make_shared<Pipeline>(root);
}

//�q�[�v����
void Compute::CreateHeap(const size_t& num)
{
	create::CreateHeap(&heap, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV
						, D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE, num);

	rsc.resize(num);
}

//�萔���\�[�X����
int Compute::CreateCRsc(const size_t& size)
{
	D3D12_HEAP_PROPERTIES prop{};
	prop.Type = D3D12_HEAP_TYPE_UPLOAD;


	D3D12_RESOURCE_DESC desc{};
	desc.DepthOrArraySize = 1;
	desc.Dimension = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Height = 1;
	desc.Width = (size + 0xff) & ~0xff;
	desc.Layout = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.MipLevels = 1;
	desc.SampleDesc = { 1,0 };

	create::CreateRsc(&rsc[index].rsc, prop, desc, nullptr, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ);
	create::Map(rsc[index].rsc.Get(), &rsc[index].data);

	return index++;
}

//�񏇏����\�[�X����
int Compute::CreateURsc(const size_t& stride, const size_t& num)
{
	D3D12_HEAP_PROPERTIES prop;
	prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_L0;
	prop.Type = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_CUSTOM;

	D3D12_RESOURCE_DESC desc{};
	desc.DepthOrArraySize = 1;
	desc.Dimension = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Flags = D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
	desc.Height = 1;
	desc.Width = unsigned __int64(stride * num);
	desc.Layout = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.MipLevels = 1;
	desc.SampleDesc = { 1,0 };

	create::CreateRsc(&rsc[index].rsc, prop, desc, nullptr, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ);
	create::Map(rsc[index].rsc.Get(), &rsc[index].data);

	return index++;
}

//GPU�������ɃR�s�[
void Compute::Copy(const int& id, void* data, const size_t& size)
{
	memcpy(rsc[id].data, data, size);
}

//���s
void Compute::Execution(const unsigned int& x, const unsigned int& y, const unsigned int& z)
{
	allo->Get()->Reset();
	list->Get()->Reset(allo->Get(), nullptr);

	list->Get()->SetComputeRootSignature(root->Get());
	list->Get()->SetPipelineState(pipe->Get());
	list->Get()->SetDescriptorHeaps(1, heap.GetAddressOf());

	for (unsigned int i = 0; i < rsc.size(); i++)
	{
		list->SetComputeTable(i , heap.Get(), i);
	}

	list->Get()->Dispatch(x, y, z);
	list->Get()->Close();

	ID3D12CommandList* command[] = {
		list->Get()
	};

	queue->Get()->ExecuteCommandLists(_countof(command), command);
	fence->Wait();
}

//GPU�������f�[�^�擾
template<typename T>
inline std::vector<T> Compute::GetData(const int& id)
{
	auto size = rsc[id].rsc->GetDesc().Width / sizeof(T);
	return std::vector<T>((T*)rsc[id].data, (T*)rsc[id].data + size);
}
template std::vector<int> Compute::GetData(const int&);
template std::vector<float> Compute::GetData(const int&);

//�I��
void Compute::Finish(void)
{
	for (Resource& i : rsc)
	{
		create::UnMap(i.rsc.Get());
	}
}
