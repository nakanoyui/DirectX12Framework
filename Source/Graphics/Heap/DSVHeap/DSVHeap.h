#pragma once

class DSVHeap :public Heap<int>
{
public:
	DSVHeap() {}
	~DSVHeap() {}

	/// <summary>
	/// DSV�̍쐬
	/// </summary>
	/// <param name="pBuffer">�o�b�t�@�[�̃|�C���^</param>
	/// <param name="format">�o�b�t�@�[�̃t�H�[�}�b�g</param>
	/// <returns>�q�[�v�̕R�t����ꂽ�o�^�ԍ�</returns>
	int CreateDSV(ID3D12Resource* pBuffer, DXGI_FORMAT format);
private:
};