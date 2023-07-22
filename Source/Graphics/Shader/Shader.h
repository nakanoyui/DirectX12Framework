#pragma once

#include "Pipeline/Pipeline.h"
#include "RootSignature/RootSignature.h"

struct RenderingSetting
{
	std::vector<InputLayout> InputLayouts;
	std::vector<DXGI_FORMAT> Formats;
	CullMode CullMode = CullMode::Back;
	BlendMode BlendMode = BlendMode::Alpha;
	PrimitiveTopologyType PrimitiveTopologyType = PrimitiveTopologyType::Triangle;
	bool IsDepth = true;
	bool IsDepthMask = true;
	int RTVCount = 1;
	bool IsWireFrame = false;
};

class Shader
{
public:

	/// <summary>
	/// �쐬
	/// </summary>
	/// <param name="pGraphicsDevice">�O���t�B�b�N�X�f�o�C�X�̃|�C���^</param>
	/// <param name="filePath">�t�@�C���p�X</param>
	/// <param name="renderingSetting">�`��ݒ�</param>
	/// <param name="rangeTypes">�����W�^�C�v</param>
	void Create(GraphicsDevice* pGraphicsDevice, const std::wstring& filePath,
		const RenderingSetting& renderingSetting, const std::vector<RangeType>& rangeTypes);

	/// <summary>
	/// �`��J�n
	/// </summary>
	/// <param name="w">����</param>
	/// <param name="h">�c��</param>
	void Begin(int w, int h);

	/// <summary>
	/// ���b�V���̕`��
	/// </summary>
	/// <param name="mesh">���b�V��</param>
	void DrawMesh(const Mesh& mesh);

	/// <summary>
	/// ���f���̕`��
	/// </summary>
	/// <param name="modelData">���f���f�[�^</param>
	void DrawModel(const ModelData& modelData);

	/// <summary>
	/// CBV�J�E���g�擾
	/// </summary>
	/// <returns>CBV�J�E���g</returns>
	UINT GetCBVCount() const { return m_cbvCount; }

private:

	/// <summary>
	/// �V�F�[�_�[�t�@�C���̃��[�h
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X</param>
	void LoadShaderFile(const std::wstring& filePath);

	/// <summary>
	/// �}�e���A�����Z�b�g
	/// </summary>
	/// <param name="material">�}�e���A�����</param>
	void SetMaterial(const Material& material);

	GraphicsDevice* m_pDevice = nullptr;

	std::unique_ptr<Pipeline>		m_upPipeline = nullptr;
	std::unique_ptr<RootSignature>	m_upRootSignature = nullptr;

	ID3DBlob* m_pVSBlob = nullptr;		// ���_�V�F�[�_�[
	ID3DBlob* m_pHSBlob = nullptr;		// �n���V�F�[�_�[
	ID3DBlob* m_pDSBlob = nullptr;		// �h���C���V�F�[�_�[
	ID3DBlob* m_pGSBlob = nullptr;		// �W�I���g���V�F�[�_�[
	ID3DBlob* m_pPSBlob = nullptr;		// �s�N�Z���V�F�[�_�[

	UINT m_cbvCount = 0;
};