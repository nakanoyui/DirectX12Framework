#pragma once

class CBVSRVUAVHeap :public Heap<Math::Vector3>
{
public:
	CBVSRVUAVHeap() {}
	~CBVSRVUAVHeap() {}

	/// <summary>
	/// SRVの作成
	/// </summary>
	/// <param name="pBuffer">バッファーのポインタ</param>
	/// <returns>ヒープの紐付けられた登録番号</returns>
	int CreateSRV(ID3D12Resource* pBuffer);

	/// <summary>
	/// SRVのGPU側アドレスを返す
	/// </summary>
	/// <param name="number">登録番号</param>
	/// <returns>SRVのGPU側アドレス</returns>
	const D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle(int number)override;

	/// <summary>
	/// ヒープをセットする関数
	/// </summary>
	void SetHeap();

	/// <summary>
	/// ヒープの取得関数
	/// </summary>
	/// <returns></returns>
	ID3D12DescriptorHeap* GetHeap() { return m_pHeap.Get(); }

	/// <summary>
	/// 使用数を取得
	/// </summary>
	/// <returns>使用数</returns>
	const Math::Vector3& GetUseCount() { return m_useCount; }

private:
};