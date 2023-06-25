#pragma once

enum class RangeType
{
	CBV,
	SRV,
	UAV,
};

enum class TextureAddressMode
{
	Wrap,
	Clamp,
};

enum class D3D12Filter
{
	Point,
	Linear,
};

class RootSignature
{
public:

	/// <summary>
	/// �쐬
	/// </summary>
	/// <param name="pGraphicsDevice">�O���t�B�b�N�X�f�o�C�X�̃|�C���^</param>
	/// <param name="rangeTypes">�����W�^�C�v���X�g</param>
	/// <param name="cbvCount">CBV��</param>
	void Create(GraphicsDevice* pGraphicsDevice, const std::vector<RangeType>& rangeTypes, UINT& cbvCount);

	/// <summary>
	/// ���[�g�V�O�l�`���̎擾
	/// </summary>
	/// <returns>���[�g�V�O�l�`���̃|�C���^</returns>
	ID3D12RootSignature* GetRootSignature() { return m_pRootSignature.Get(); }

private:

	/// <summary>
	/// �����W�̍쐬
	/// </summary>
	/// <param name="pRange">�����W�̃|�C���^</param>
	/// <param name="type">�����W�^�C�v</param>
	/// <param name="count">�o�^��</param>
	void CreateRange(D3D12_DESCRIPTOR_RANGE& pRange, RangeType type, int count);

	/// <summary>
	/// �T���v���[�̍쐬
	/// </summary>
	/// <param name="pSamplerDesc">�T���v���[�f�X�N�̃|�C���^</param>
	/// <param name="mode">�A�h���X���[�h</param>
	/// <param name="filter">�t�B���^�[</param>
	/// <param name="count">�g�p�T���v���[��</param>
	void CreateStaticSampler(D3D12_STATIC_SAMPLER_DESC& samplerDesc, TextureAddressMode mode,
		D3D12Filter filter, int count);

	GraphicsDevice* m_pDevice = nullptr;
	ComPtr<ID3DBlob> m_pRootBlob = nullptr;
	ComPtr<ID3D12RootSignature> m_pRootSignature = nullptr;
};