#pragma once

class RTVHeap
{
public:

	/// <summary>
	/// ヒープ作成
	/// </summary>
	/// <param name="pDevice">デバイスのポインタ</param>
	/// <param name="useCount">使用個数</param>
	/// <returns>成功したらtrue</returns>
	bool Create(ID3D12Device* pDevice, int useCount);

	/// <summary>
	/// RTVの作成
	/// </summary>
	/// <param name="pBuffer">バッファーのポインタ</param>
	/// <returns>ヒープの紐付けられた登録番号</returns>
	int CreateRTV(ID3D12Resource* pBuffer);

	/// <summary>
	/// RTVのCPU側アドレスを返す関数
	/// </summary>
	/// <param name="number">登録番号</param>
	/// <returns>SRVのGPU側アドレス</returns>
	D3D12_CPU_DESCRIPTOR_HANDLE GetRTVCPUHandle(int number);

private:
	ID3D12Device* m_pDevice = nullptr;
	ComPtr<ID3D12DescriptorHeap> m_pHeap = nullptr;
	int m_useCount = 0;
	int m_incrementSize = 0;
	int m_nextRegistNumber = 0;
};