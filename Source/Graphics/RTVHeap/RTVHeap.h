#pragma once

class RTVHeap
{
public:

	/// <summary>
	/// �q�[�v�쐬
	/// </summary>
	/// <param name="pDevice">�f�o�C�X�̃|�C���^</param>
	/// <param name="useCount">�g�p��</param>
	/// <returns>����������true</returns>
	bool Create(ID3D12Device* pDevice, int useCount);

	/// <summary>
	/// RTV�̍쐬
	/// </summary>
	/// <param name="pBuffer">�o�b�t�@�[�̃|�C���^</param>
	/// <returns>�q�[�v�̕R�t����ꂽ�o�^�ԍ�</returns>
	int CreateRTV(ID3D12Resource* pBuffer);

	/// <summary>
	/// RTV��CPU���A�h���X��Ԃ��֐�
	/// </summary>
	/// <param name="number">�o�^�ԍ�</param>
	/// <returns>SRV��GPU���A�h���X</returns>
	D3D12_CPU_DESCRIPTOR_HANDLE GetRTVCPUHandle(int number);

private:
	ID3D12Device* m_pDevice = nullptr;
	ComPtr<ID3D12DescriptorHeap> m_pHeap = nullptr;
	int m_useCount = 0;
	int m_incrementSize = 0;
	int m_nextRegistNumber = 0;
};