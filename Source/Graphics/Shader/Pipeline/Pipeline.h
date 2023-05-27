#pragma once

enum class CullMode
{
	None = D3D12_CULL_MODE_NONE,
	Front = D3D12_CULL_MODE_FRONT,
	Back = D3D12_CULL_MODE_BACK,
};

enum class BlendMode
{
	Add,
	Alpha,
};

enum class InputLayout
{
	POSITION,
	TEXCOORD,
	NORMAL,
	TANGENT,
	COLOR,
	SKININDEX,
	SKINWEIGHT
};

enum class PrimitiveTopologyType
{
	Undefined = D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED,
	Point = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT,
	Line = D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE,
	Triangle = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE,
	Patch = D3D12_PRIMITIVE_TOPOLOGY_TYPE_PATCH,
};

class RootSignature;

class Pipeline
{
public:

	/// <summary>
	/// �`��ݒ�̃Z�b�g
	/// </summary>
	/// <param name="pGraphicsDevice">�O���t�B�b�N�X�f�o�C�X�̃|�C���^</param>
	/// <param name="pRootSignature">���[�g�V�O�l�`���̃|�C���^</param>
	/// <param name="inputLayouts">���_���C�A�E�g���</param>
	/// <param name="cullMode">�J�����O���[�h</param>
	/// <param name="blendMode">�u�����h���[�h</param>
	/// <param name="topologyType">�v���~�e�B�u�g�|���W�[</param>
	void SetRenderSettings(GraphicsDevice* pGraphicsDevice, RootSignature* pRootSignature,
		const std::vector<InputLayout>& inputLayouts, CullMode cullMode, BlendMode blendMode,
		PrimitiveTopologyType topologyType);

	/// <summary>
	/// �쐬
	/// </summary>
	/// <param name="pBlobs">�V�F�[�_�[�f�[�^���X�g</param>
	/// <param name="formats">�t�H�[�}�b�g���X�g</param>
	/// <param name="isDepth">�[�x�e�X�g</param>
	/// <param name="isDepthMask">�[�x��������</param>
	/// <param name="rtvCount">RTV��</param>
	/// <param name="isWireFrame">���C���[�t���[�����ǂ���</param>
	void Create(std::vector<ID3DBlob*> pBlobs, const std::vector<DXGI_FORMAT> formats, bool isDepth, bool isDepthMask,
		int rtvCount, bool isWireFrame);

	/// <summary>
	/// �p�C�v���C���̎擾
	/// </summary>
	/// <returns>�p�C�v���C��</returns>
	ID3D12PipelineState* GetPipeline() { return m_pPipelineState.Get(); }

	/// <summary>
	/// �g�|���W�[�^�C�v�̎擾
	/// </summary>
	/// <returns>�g�|���W�[�^�C�v</returns>
	PrimitiveTopologyType GetTopologyType() { return m_topologyType; }

private:

	void SetInputLayout(std::vector<D3D12_INPUT_ELEMENT_DESC>& inputElements,
		const std::vector<InputLayout>& inputLayouts);

	/// <summary>
	/// �u�����h���[�h�̃Z�b�g
	/// </summary>
	/// <param name="blendDesc">�����_�[�^�[�Q�b�g�u�����h���</param>
	/// <param name="blendMode">�u�����h���[�h</param>
	void SetBlendMode(D3D12_RENDER_TARGET_BLEND_DESC& blendDesc, BlendMode blendMode);

	GraphicsDevice* m_pDevice = nullptr;
	RootSignature* m_pRootSignature = nullptr;

	std::vector<InputLayout>	m_inputLayouts;
	CullMode					m_cullMode;
	BlendMode					m_blendMode;
	PrimitiveTopologyType		m_topologyType;

	ComPtr<ID3D12PipelineState> m_pPipelineState = nullptr;
};