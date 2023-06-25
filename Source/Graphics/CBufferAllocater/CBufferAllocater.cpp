#include "CBufferAllocater.h"

void CBufferAllocater::Create(GraphicsDevice* pGraphicsDevice, CBVSRVUAVHeap* pHeap)
{
	m_pGraphicsDevice = pGraphicsDevice;
	m_pHeap = pHeap;

	D3D12_HEAP_PROPERTIES heapprop = {};
	heapprop.Type = D3D12_HEAP_TYPE_UPLOAD;
	D3D12_RESOURCE_DESC resDesc = {};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	resDesc.Width = (UINT64)((1 + 0xff) & ~0xff) * (int)m_pHeap->GetUseCount().x;
	HRESULT result = m_pGraphicsDevice->GetDevice()->CreateCommittedResource
	(&heapprop, D3D12_HEAP_FLAG_NONE, &resDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_pBuffer));

	if (FAILED(result))
	{
		assert(0 && "CBufferAllocater‚Ìì¬Ž¸”s");
		return;
	}

	m_pBuffer->Map(0, nullptr, (void**)&m_pMappedBuffer);
}

void CBufferAllocater::ResetCurrentUseNumber()
{
	m_currentUseNumber = 0;
}