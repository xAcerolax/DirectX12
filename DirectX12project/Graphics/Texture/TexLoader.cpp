#include "TexLoader.h"
#include "WICTextureLoader12.h"
#include "../Device/Device.h"
#include "../../Func/Func.h"
#include <d3d12.h>

// �R���X�g���N�^
TexLoader::TexLoader()
{
}

// �f�X�g���N�^
TexLoader::~TexLoader()
{
}

// �ǂݍ���
void TexLoader::Load(const std::string& fileName)
{
	if (rsc.find(fileName) == rsc.end())
	{
		sub[fileName] = std::make_shared<D3D12_SUBRESOURCE_DATA>();
		auto hr = DirectX::LoadWICTextureFromFile(Device::Get().Dev(), create::ChangeCode(fileName).c_str(),
			&rsc[fileName], decode[fileName], *sub[fileName]);
		_ASSERT(hr == S_OK);

		D3D12_BOX box{};
		box.back = 1;
		box.bottom = rsc[fileName]->GetDesc().Height;
		box.right = unsigned int(rsc[fileName]->GetDesc().Width);

		hr = rsc[fileName]->WriteToSubresource(0, &box, &decode[fileName][0],
			unsigned int(sub[fileName]->RowPitch), unsigned int(sub[fileName]->SlicePitch));
		_ASSERT(hr == S_OK);
	}
}

// �f�[�^�폜
void TexLoader::Delete(const std::string& fileName)
{
	if (rsc.find(fileName) != rsc.end())
	{
		rsc.erase(rsc.find(fileName));
		decode.erase(decode.find(fileName));
		sub.erase(sub.find(fileName));
	}
}

// ���\�[�X�擾
ID3D12Resource* TexLoader::Rsc(const std::string& fileName)
{
	if (rsc.find(fileName) != rsc.end())
	{
		return rsc[fileName].Get();
	}

	return nullptr;
}

// �f�R�[�h�f�[�^�擾
unsigned char* TexLoader::Decode(const std::string& fileName)
{
	if (decode.find(fileName) != decode.end())
	{
		return decode[fileName].get();
	}

	return nullptr;
}

// �T�u�f�[�^�擾
std::shared_ptr<D3D12_SUBRESOURCE_DATA> TexLoader::SubData(const std::string& fileName)
{
	if (sub.find(fileName) != sub.end())
	{
		return sub[fileName];
	}

	return nullptr;
}

// �摜�T�C�Y�擾
Vec2f TexLoader::GetSize(const std::string& fileName)
{
	return Vec2f(float(rsc[fileName]->GetDesc().Width), float(rsc[fileName]->GetDesc().Height));
}