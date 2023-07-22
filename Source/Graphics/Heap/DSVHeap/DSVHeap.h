#pragma once

class DSVHeap :public Heap<int>
{
public:
	DSVHeap() {}
	~DSVHeap() {}

	/// <summary>
	/// DSVの作成
	/// </summary>
	/// <param name="pBuffer">バッファーのポインタ</param>
	/// <param name="format">バッファーのフォーマット</param>
	/// <returns>ヒープの紐付けられた登録番号</returns>
	int CreateDSV(ID3D12Resource* pBuffer, DXGI_FORMAT format);
private:
};