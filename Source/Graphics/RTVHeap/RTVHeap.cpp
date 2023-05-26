#include "RTVHeap.h"

bool RTVHeap::Create(ID3D12Device* pDevice, int useCount)
{
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};

	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;		// レンダーターゲットとして扱う
	heapDesc.NodeMask = 0;
	heapDesc.NumDescriptors = useCount;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;	// 特に指定なし

	auto hr = pDevice->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&m_pHeap));

	if (FAILED(hr))
	{
		return false;
	}

	m_useCount = useCount;
	m_incrementSize = pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	m_pDevice = pDevice;

	return true;
}

int RTVHeap::CreateRTV(ID3D12Resource* pBuffer)
{
	if (m_useCount < m_nextRegistNumber)
	{
		assert(0 && "確保済みのヒープ領域を超えました。");
		return 0;
	}

	D3D12_CPU_DESCRIPTOR_HANDLE handle = m_pHeap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += (UINT64)m_nextRegistNumber * m_incrementSize;
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
	m_pDevice->CreateRenderTargetView(pBuffer, &rtvDesc, handle);
	return m_nextRegistNumber++;
}

D3D12_CPU_DESCRIPTOR_HANDLE RTVHeap::GetRTVCPUHandle(int number)
{
	D3D12_CPU_DESCRIPTOR_HANDLE handle = m_pHeap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += (UINT64)m_incrementSize * number;
	return handle;
}