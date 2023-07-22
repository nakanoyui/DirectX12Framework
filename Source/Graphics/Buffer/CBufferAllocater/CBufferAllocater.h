#pragma once

class CBufferAllocater :public Buffer
{
public:

	/// <summary>
	/// 作成
	/// </summary>
	/// <param name="pGraphicsDevice">グラフィックスデバイスのポインタ</param>
	/// <param name="pHeap">CBVSRVUAVHeapのポインタ</param>
	void Create(GraphicsDevice* pGraphicsDevice, CBVSRVUAVHeap* pHeap);

	/// <summary>
	/// 使用しているバッファの番号を初期化
	/// </summary>
	void ResetCurrentUseNumber();

	/// <summary>
	/// 定数バッファーにデータのバインドを行う
	/// </summary>
	/// <param name="descIndex">レジスタ番号</param>
	/// <param name="data">バインドデータ</param>
	template<typename T>
	void BindAndAttachData(int descIndex, const T& data);

private:
	CBVSRVUAVHeap* m_pHeap = nullptr;
	struct { char buf[256]; }*m_pMappedBuffer = nullptr;
	int m_currentUseNumber = 0;
};

template<typename T>
inline void CBufferAllocater::BindAndAttachData(int descIndex, const T& data)
{
	if (!m_pHeap)return;

	// dataサイズを256アライメントして計算
	int sizeAligned = (sizeof(T) + 0xff) & ~0xff;

	// 256byteをいくつ使用するかアライメントした結果を256で割って計算
	int useValue = sizeAligned / 0x100;

	// 現在使い終わっている番号と今から使う容量がヒープの容量を超えている場合はリターン
	if (m_currentUseNumber + useValue > (int)m_pHeap->GetUseCount().x)
	{
		assert(0 && "使用できるヒープ容量を超えました");
		return;
	}

	int top = m_currentUseNumber;

	// 先頭アドレスに使う分のポインタを足してmemcpy
	memcpy(m_pMappedBuffer + top, &data, sizeof(T));

	// ビューを作って値をシェーダーにアタッチ
	D3D12_CONSTANT_BUFFER_VIEW_DESC cbDesc = {};
	cbDesc.BufferLocation = m_pBuffer->GetGPUVirtualAddress() + (UINT64)top * 0x100;
	cbDesc.SizeInBytes = sizeAligned;

	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = m_pHeap->GetHeap()->GetCPUDescriptorHandleForHeapStart();
	cpuHandle.ptr += (UINT64)m_pGraphicsDevice->GetDevice()->GetDescriptorHandleIncrementSize
	(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV) *m_currentUseNumber;

	m_pGraphicsDevice->GetDevice()->CreateConstantBufferView(&cbDesc, cpuHandle);

	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle = m_pHeap->GetHeap()->GetGPUDescriptorHandleForHeapStart();
	gpuHandle.ptr += (UINT64)m_pGraphicsDevice->GetDevice()->GetDescriptorHandleIncrementSize
	(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV) *m_currentUseNumber;

	m_pGraphicsDevice->GetCmdList()->SetGraphicsRootDescriptorTable(descIndex, gpuHandle);

	m_currentUseNumber += useValue;
}