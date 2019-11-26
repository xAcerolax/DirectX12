#pragma once
#include "../../Single.h"
#include "../../Vector/Vector2.h"
#include <wrl.h>
#include <string>
#include <memory>
#include <unordered_map>

struct D3D12_SUBRESOURCE_DATA;
struct ID3D12Resource;

class TexLoader :
	public Single<TexLoader>
{
	friend Single<TexLoader>;
public:
	// �ǂݍ���
	void Load(const std::string& fileName);

	// �f�[�^�폜
	void Delete(const std::string& fileName);

	// ���\�[�X�擾
	ID3D12Resource* Rsc(const std::string& fileName);

	// �f�R�[�h�f�[�^�擾
	unsigned char* Decode(const std::string& fileName);

	// �T�u�f�[�^�擾
	std::shared_ptr<D3D12_SUBRESOURCE_DATA> SubData(const std::string& fileName);

	// �摜�T�C�Y�擾
	Vec2f GetSize(const std::string& fileName);

private:
	// �R���X�g���N�^
	TexLoader();
	// �f�X�g���N�^
	~TexLoader();


	// ���\�[�X
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D12Resource>>rsc;

	// �f�R�[�h
	std::unordered_map<std::string, std::unique_ptr<unsigned char[]>>decode;

	// �T�u�f�[�^
	std::unordered_map<std::string, std::shared_ptr<D3D12_SUBRESOURCE_DATA>>sub;
};