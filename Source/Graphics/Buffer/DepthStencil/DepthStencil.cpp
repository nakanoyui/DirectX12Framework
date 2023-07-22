#include "DepthStencil.h"

bool DepthStencil::Create(GraphicsDevice* pGraphicsDevice, const Math::Vector2& resolution, DepthStencilFormat format)
{
	m_pGraphicsDevice = pGraphicsDevice;

	// �f�v�X�o�b�t�@�ݒ�
	D3D12_HEAP_PROPERTIES heapProp = {};
	heapProp.Type = D3D12_HEAP_TYPE_DEFAULT;

	D3D12_RESOURCE_DESC resDesc = {};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	resDesc.Width = static_cast<UINT>(resolution.x);
	resDesc.Height = static_cast<UINT>(resolution.y);
	resDesc.DepthOrArraySize = 1;
	resDesc.Format = static_cast<DXGI_FORMAT>(format);
	resDesc.SampleDesc.Count = 1;
	resDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	// �f�v�X�o�b�t�@�̃t�H�[�}�b�g�ƍő�[�x�l��ݒ�
	D3D12_CLEAR_VALUE depthClearValue = {};
	depthClearValue.DepthStencil.Depth = 1.0f;

	switch (format)
	{
	case DepthStencilFormat::DepthLowQuality:
		depthClearValue.Format = DXGI_FORMAT_D16_UNORM;
		break;
	case DepthStencilFormat::DepthHighQuality:
		depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;
		break;
	case DepthStencilFormat::DepthHighQualityAndStencil:
		depthClearValue.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		break;
	default:
		break;
	}

	// �ݒ�����Ƀf�v�X�o�b�t�@�𐶐�
	auto hr = m_pGraphicsDevice->GetDevice()->CreateCommittedResource(
		&heapProp, D3D12_HEAP_FLAG_NONE, &resDesc, D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&depthClearValue, IID_PPV_ARGS(&m_pBuffer));

	if (FAILED(hr))
	{
		assert(0 && "�f�v�X�X�e���V���o�b�t�@�̍쐬���s");
		return false;
	}

	// DSV�쐬
	m_dsvNumber = m_pGraphicsDevice->GetDSVHeap()->CreateDSV(m_pBuffer.Get(), depthClearValue.Format);

	return true;
}

void DepthStencil::ClearBuffer()
{
	m_pGraphicsDevice->GetCmdList()->ClearDepthStencilView(
		m_pGraphicsDevice->GetDSVHeap()->GetCPUHandle(m_dsvNumber), D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}
