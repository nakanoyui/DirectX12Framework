#pragma once

class RTVHeap :public Heap<int>
{
public:
	RTVHeap() {}
	~RTVHeap() {}

	/// <summary>
	/// RTVの作成
	/// </summary>
	/// <param name="pBuffer">バッファーのポインタ</param>
	/// <returns>ヒープの紐付けられた登録番号</returns>
	int CreateRTV(ID3D12Resource* pBuffer);

private:
};