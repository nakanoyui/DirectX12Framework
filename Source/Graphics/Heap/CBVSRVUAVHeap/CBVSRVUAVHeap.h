#pragma once

class CBVSRVUAVHeap :public Heap<Math::Vector3>
{
public:
	CBVSRVUAVHeap() {}
	~CBVSRVUAVHeap() {}

	/// <summary>
	/// SRV�̍쐬
	/// </summary>
	/// <param name="pBuffer">�o�b�t�@�[�̃|�C���^</param>
	/// <returns>�q�[�v�̕R�t����ꂽ�o�^�ԍ�</returns>
	int CreateSRV(ID3D12Resource* pBuffer);

	/// <summary>
	/// SRV��GPU���A�h���X��Ԃ�
	/// </summary>
	/// <param name="number">�o�^�ԍ�</param>
	/// <returns>SRV��GPU���A�h���X</returns>
	const D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle(int number)override;

	/// <summary>
	/// �q�[�v���Z�b�g����֐�
	/// </summary>
	void SetHeap();

	/// <summary>
	/// �q�[�v�̎擾�֐�
	/// </summary>
	/// <returns></returns>
	ID3D12DescriptorHeap* GetHeap() { return m_pHeap.Get(); }

	/// <summary>
	/// �g�p�����擾
	/// </summary>
	/// <returns>�g�p��</returns>
	const Math::Vector3& GetUseCount() { return m_useCount; }

private:
};