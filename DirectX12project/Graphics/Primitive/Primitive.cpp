#include "Primitive.h"
#include "../List/List.h"
#include "../Descriptor/Descriptor.h"
#include <d3d12.h>


//コンストラクタ
Primitive::Primitive(std::weak_ptr<List> list, const create::PrimType & type)
	:list(list), heap(nullptr), vRsc(nullptr), cRsc(nullptr), color(nullptr)
{
}

Primitive::~Primitive()
{
}

//初期化
void Primitive::Init(void)
{
	create::CreateHeap(&heap, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
		D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE);

	CreateVRsc();
	CreateCRsc();
}

//頂点リソース生成
void Primitive::CreateVRsc(void)
{
	D3D12_HEAP_PROPERTIES prop{};

	prop.Type = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD;


	D3D12_RESOURCE_DESC desc{};

	desc.DepthOrArraySize = 1;
	desc.Dimension = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Height = 1;
	desc.Width = unsigned __int64(sizeof(vertex[0]) * vertex.size());
	desc.Layout = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.MipLevels = 1;
	desc.SampleDesc = { 1,0 };
	
	create::CreateRsc(&vRsc, prop, desc, nullptr, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ);
}

//定数リソース生成
void Primitive::CreateCRsc(void)
{
	D3D12_HEAP_PROPERTIES prop{};

	prop.Type = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD;


	D3D12_RESOURCE_DESC desc{};

	desc.DepthOrArraySize = 1;
	desc.Dimension = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Height = 1;
	desc.Width = (sizeof(create::Color) + 0xff) & ~0xff;
	desc.Layout = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.MipLevels = 1;
	desc.SampleDesc = { 1,0 };
	
	create::CreateRsc(&cRsc, prop, desc, nullptr, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ);
}

//ポイント描画
void Primitive::DrawPoint(const Vec2f & pos, const create::Color & color)
{
	vertex[0] = pos;

	void* data = nullptr;

}

void Primitive::DrawLine(const Vec2f & pos1, const Vec2f & pos2, const create::Color & color)
{
	vertex[0] = pos1;
	vertex[1] = pos2;

	void* data = nullptr;

}

void Primitive::DrawTriangle(const Vec2f & pos1, const Vec2f & pos2, const Vec2f & pos3, const create::Color & color)
{
}

void Primitive::DrawBox(const Vec2f & pos, const Vec2f & size, const create::Color & color)
{
}

void Primitive::Draw(void)
{
	D3D12_VERTEX_BUFFER_VIEW desc{};

	desc.BufferLocation = vRsc->GetGPUVirtualAddress();
	desc.SizeInBytes = unsigned int(vRsc->GetDesc().Width);
	desc.StrideInBytes = sizeof(vertex[0]);

	list.lock()->Get()->IASetVertexBuffers(0, 1, &desc);
	list.lock()->Get()->SetDescriptorHeaps(1, heap.GetAddressOf());
	list.lock()->SetGraphicsTable(1, heap.Get());
	list.lock()->Get()->DrawInstanced(unsigned int(vertex.size()), 1, 0, 0);
}
