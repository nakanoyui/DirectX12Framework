#include "Pipeline.h"

#include "../RootSignature/RootSignature.h"

void Pipeline::SetRenderSettings(GraphicsDevice* pGraphicsDevice, RootSignature* pRootSignature, const std::vector<InputLayout>& inputLayouts, CullMode cullMode, BlendMode blendMode, PrimitiveTopologyType topologyType)
{
	m_pDevice = pGraphicsDevice;
	m_pRootSignature = pRootSignature;
	m_inputLayouts = inputLayouts;
	m_cullMode = cullMode;
	m_blendMode = blendMode;
	m_topologyType = topologyType;
}

void Pipeline::Create(std::vector<ID3DBlob*> pBlobs, const std::vector<DXGI_FORMAT> formats, bool bDepth, bool bDepthMask, int rtvCount, bool bWireFrame)
{
	std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayouts;
	SetInputLayout(inputLayouts, m_inputLayouts);

	// GraphicsPipelineState�̊e��ݒ�
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineState = {};

	// ���_�V�F�[�_�[���Z�b�g
	graphicsPipelineState.VS.pShaderBytecode = pBlobs[0]->GetBufferPointer();
	graphicsPipelineState.VS.BytecodeLength = pBlobs[0]->GetBufferSize();

	// �n���V�F�[�_�[���Z�b�g
	if (pBlobs[1])
	{
		graphicsPipelineState.HS.pShaderBytecode = pBlobs[1]->GetBufferPointer();
		graphicsPipelineState.HS.BytecodeLength = pBlobs[1]->GetBufferSize();
	}

	// �h���C���V�F�[�_�[���Z�b�g
	if (pBlobs[2])
	{
		graphicsPipelineState.DS.pShaderBytecode = pBlobs[2]->GetBufferPointer();
		graphicsPipelineState.DS.BytecodeLength = pBlobs[2]->GetBufferSize();
	}

	// �W�I���g���V�F�[�_�[���Z�b�g
	if (pBlobs[3])
	{
		graphicsPipelineState.GS.pShaderBytecode = pBlobs[3]->GetBufferPointer();
		graphicsPipelineState.GS.BytecodeLength = pBlobs[3]->GetBufferSize();
	}

	// �s�N�Z���V�F�[�_�[���Z�b�g
	graphicsPipelineState.PS.pShaderBytecode = pBlobs[4]->GetBufferPointer();
	graphicsPipelineState.PS.BytecodeLength = pBlobs[4]->GetBufferSize();

	graphicsPipelineState.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

	// �J�����O���[�h���Z�b�g
	graphicsPipelineState.RasterizerState.CullMode = static_cast<D3D12_CULL_MODE>(m_cullMode);

	// �t�B���^�[���[�h���Z�b�g
	if (bWireFrame)
	{
		graphicsPipelineState.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;		// ���g��h��Ԃ��Ȃ�
	}
	else
	{
		graphicsPipelineState.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;			// ���g��h��Ԃ�
	}

	// �[�x�ݒ���Z�b�g
	if (bDepth)
	{
		graphicsPipelineState.RasterizerState.DepthClipEnable = true;
		graphicsPipelineState.DepthStencilState.DepthEnable = true;

		if (bDepthMask)
		{
			graphicsPipelineState.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
		}
		else
		{
			graphicsPipelineState.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
		}
		graphicsPipelineState.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
		graphicsPipelineState.DSVFormat = DXGI_FORMAT_D32_FLOAT;
	}
	else
	{
		graphicsPipelineState.RasterizerState.DepthClipEnable = false;
		graphicsPipelineState.DepthStencilState.DepthEnable = false;
	}

	graphicsPipelineState.BlendState.AlphaToCoverageEnable = false;

	graphicsPipelineState.BlendState.IndependentBlendEnable = false;

	// �u�����h�ݒ�
	D3D12_RENDER_TARGET_BLEND_DESC blendDesc = {};
	SetBlendMode(blendDesc, m_blendMode);

	graphicsPipelineState.BlendState.RenderTarget[0] = blendDesc;

	graphicsPipelineState.InputLayout.pInputElementDescs = inputLayouts.data();			// ���C�A�E�g�擪�A�h���X
	graphicsPipelineState.InputLayout.NumElements = (int)m_inputLayouts.size();			// ���C�A�E�g�z��̗v�f��

	graphicsPipelineState.PrimitiveTopologyType = (pBlobs[3] && pBlobs[4]) ? 
		D3D12_PRIMITIVE_TOPOLOGY_TYPE_PATCH : static_cast<D3D12_PRIMITIVE_TOPOLOGY_TYPE>(m_topologyType);
	
	// RTV�����Z�b�g
	graphicsPipelineState.NumRenderTargets = rtvCount;

	// RTV�t�H�[�}�b�g�̃Z�b�g
	for (int i = 0; i < rtvCount; ++i)
	{
		graphicsPipelineState.RTVFormats[i] = formats[i];
	}

	graphicsPipelineState.SampleDesc.Count = 1;		// �T���v�����O��1�s�N�Z���ɂ�1
	graphicsPipelineState.pRootSignature = m_pRootSignature->GetRootSignature();

	auto hr = m_pDevice->GetDevice()->CreateGraphicsPipelineState(&graphicsPipelineState, IID_PPV_ARGS(&m_pPipelineState));

	if (FAILED(hr))
	{
		assert(0 && "�p�C�v���C���X�e�[�g�̍쐬�Ɏ��s���܂���");
		return;
	}
}

void Pipeline::SetInputLayout(std::vector<D3D12_INPUT_ELEMENT_DESC>& inputElements, const std::vector<InputLayout>& inputLayouts)
{
	for (int i = 0; i < (int)inputLayouts.size(); ++i)
	{
		if (inputLayouts[i] == InputLayout::POSITION)
		{
			inputElements.emplace_back(D3D12_INPUT_ELEMENT_DESC{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
				D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
		}
		else if (inputLayouts[i] == InputLayout::TEXCOORD)
		{
			inputElements.emplace_back(D3D12_INPUT_ELEMENT_DESC{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,
				D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA ,0 });
		}
		else if (inputLayouts[i] == InputLayout::NORMAL)
		{
			inputElements.emplace_back(D3D12_INPUT_ELEMENT_DESC{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
				D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
		}
		else if (inputLayouts[i] == InputLayout::COLOR)
		{
			inputElements.emplace_back(D3D12_INPUT_ELEMENT_DESC{ "COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 
				D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
		}
		else if (inputLayouts[i] == InputLayout::TANGENT)
		{
			inputElements.emplace_back(D3D12_INPUT_ELEMENT_DESC{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 
				D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
		}
		else if (inputLayouts[i] == InputLayout::SKININDEX)
		{
			inputElements.emplace_back(D3D12_INPUT_ELEMENT_DESC{ "SKININDEX", 0, DXGI_FORMAT_R16G16B16A16_UINT, 0,
				D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
		}
		else if (inputLayouts[i] == InputLayout::SKINWEIGHT)
		{
			inputElements.emplace_back(D3D12_INPUT_ELEMENT_DESC{ "SKINWEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 
				D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
		}
	}
}

void Pipeline::SetBlendMode(D3D12_RENDER_TARGET_BLEND_DESC& blendDesc, BlendMode blendMode)
{
	blendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	blendDesc.BlendEnable = true;

	switch (blendMode)
	{
	case BlendMode::Add:
		// ���Z����
		blendDesc.BlendOp = D3D12_BLEND_OP_ADD;
		blendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
		blendDesc.DestBlend = D3D12_BLEND_ONE;

		blendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
		blendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;
		blendDesc.DestBlendAlpha = D3D12_BLEND_INV_SRC_ALPHA;
		blendDesc.LogicOp = D3D12_LOGIC_OP_NOOP;
		break;
	case BlendMode::Alpha:
		// ������
		blendDesc.BlendOp = D3D12_BLEND_OP_ADD;
		blendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
		blendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;

		blendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
		blendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;
		blendDesc.DestBlendAlpha = D3D12_BLEND_INV_SRC_ALPHA;
		blendDesc.LogicOp = D3D12_LOGIC_OP_NOOP;
		break;
	default:
		break;
	}
}