#pragma once
#include <wrl.h>
#include <string>

struct ID3D12RootSignature;
struct ID3D10Blob;
typedef ID3D10Blob ID3DBlob;

namespace create
{
	// �V�F�[�_�R���p�C��
	void ShaderCompile(const std::string& fileName, const std::string& func, const std::string& ver, ID3DBlob** blob);

	// .cso�ǂݍ���
	void ShaderLoad(const std::string& fileName, ID3DBlob** blob);

	// ���\�[�X�ǂݍ���
	void ShaderRead(const int& id, ID3DBlob** blob);
}

class RootSignature
{
public:
	// �R���X�g���N�^
	RootSignature();
	// �f�X�g���N�^
	~RootSignature();

	// �V�F�[�_�R���p�C��
	void Vertex(const std::string& fileName, const std::string& func, const std::string& ver);
	void Geometry(const std::string& fileName, const std::string& func, const std::string& ver);
	void Pixel(const std::string& fileName, const std::string& func, const std::string& ver);
	void Compute(const std::string& fileName, const std::string& func, const std::string& ver);

	// .cso�ǂݍ���
	void Vertex(const std::string& fileName);
	void Geometry(const std::string& fileName);
	void Pixel(const std::string& fileName);
	void Compute(const std::string& fileName);

	// ���\�[�X�ǂݍ���
	void Vertex(const int& id);
	void Geometry(const int& id);
	void Pixel(const int& id);
	void Compute(const int& id);

	// ���[�g�V�O�l�`���擾
	ID3D12RootSignature* Get(void) const;

	// ���_�V�F�[�_���擾
	ID3DBlob* GetVertex(void) const;

	// �W�I���g���V�F�[�_���擾
	ID3DBlob* GetGeometry(void) const;

	// �s�N�Z���V�F�[�_���擾
	ID3DBlob* GetPixel(void) const;

	// �R���s���[�g�V�F�[�_���擾
	ID3DBlob* GetCompute(void) const;

private:
	// ���[�g�V�O�l�`������
	void CreateRoot(ID3DBlob* blob);


	// ���[�g�V�O�l�`��
	Microsoft::WRL::ComPtr<ID3D12RootSignature>root;

	// ���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3DBlob>vertex;

	// �W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3DBlob>geometry;

	// �s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3DBlob>pixel;

	// �R���s���[�g�V�F�[�_
	Microsoft::WRL::ComPtr<ID3DBlob>compute;
};

