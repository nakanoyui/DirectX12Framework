#include "CBVSRVUAVHeap.h"

int CBVSRVUAVHeap::CreateSRV(ID3D12Resource* pBuffer)
{
	if (m_useCount.y < m_nextRegistNumber)
	{
		assert(0 && "確保済みのヒープ領域を超えました。");
		return 0;
	};

	D3D12_CPU_DESCRIPTOR_HANDLE handle = m_pHeap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += ((UINT64)m_useCount.x + 1) * m_incrementSize + (UINT64)m_nextRegistNumber * m_incrementSize;
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = pBuffer->GetDesc().Format;

	if (pBuffer->GetDesc().Format == DXGI_FORMAT_R32_TYPELESS)
	{
		srvDesc.Format = DXGI_FORMAT_R32_FLOAT;
	}

	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	m_pDevice->GetDevice()->CreateShaderResourceView(pBuffer, &srvDesc, handle);

	return m_nextRegistNumber++;
}

const D3D12_GPU_DESCRIPTOR_HANDLE CBVSRVUAVHeap::GetGPUHandle(int number)
{
	D3D12_GPU_DESCRIPTOR_HANDLE handle = m_pHeap->GetGPUDescriptorHandleForHeapStart();
	handle.ptr += (UINT64)m_incrementSize * ((UINT64)m_useCount.x + 1);
	handle.ptr += (UINT64)m_incrementSize * number;
	return handle;
}

void CBVSRVUAVHeap::SetHeap()
{
	ID3D12DescriptorHeap* ppHeaps[] = { m_pHeap.Get()};
	m_pDevice->GetCmdList()->SetDescriptorHeaps(1, ppHeaps);
}