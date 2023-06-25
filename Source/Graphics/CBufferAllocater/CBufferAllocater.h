#pragma once

class CBufferAllocater
{
public:

	/// <summary>
	/// �쐬
	/// </summary>
	/// <param name="pGraphicsDevice">�O���t�B�b�N�X�f�o�C�X�̃|�C���^</param>
	/// <param name="pHeap">CBVSRVUAVHeap�̃|�C���^</param>
	void Create(GraphicsDevice* pGraphicsDevice, CBVSRVUAVHeap* pHeap);

	/// <summary>
	/// �g�p���Ă���o�b�t�@�̔ԍ���������
	/// </summary>
	void ResetCurrentUseNumber();

	/// <summary>
	/// �萔�o�b�t�@�[�Ƀf�[�^�̃o�C���h���s��
	/// </summary>
	/// <param name="descIndex">���W�X�^�ԍ�</param>
	/// <param name="data">�o�C���h�f�[�^</param>
	template<typename T>
	void BindAndAttachData(int descIndex, const T& data);

private:
	GraphicsDevice* m_pGraphicsDevice = nullptr;
	CBVSRVUAVHeap* m_pHeap = nullptr;
	ComPtr<ID3D12Resource> m_pBuffer = nullptr;
	struct { char buf[256]; }*m_pMappedBuffer = nullptr;
	int m_currentUseNumber = 0;					
};

template<typename T>
inline void CBufferAllocater::BindAndAttachData(int descIndex, const T& data)
{
	if (!m_pHeap)return;

	// data�T�C�Y��256�A���C�����g���Čv�Z
	int sizeAligned = (sizeof(T) + 0xff) & ~0xff;

	// 256byte�������g�p���邩�A���C�����g�������ʂ�256�Ŋ����Čv�Z
	int useValue = sizeAligned / 0x100;

	// ���ݎg���I����Ă���ԍ��ƍ�����g���e�ʂ��q�[�v�̗e�ʂ𒴂��Ă���ꍇ�̓��^�[��
	if (m_currentUseNumber + useValue > (int)m_pHeap->GetUseCount().x)
	{
		assert(0 && "�g�p�ł���q�[�v�e�ʂ𒴂��܂���");
		return;
	}

	int top = m_currentUseNumber;

	// �擪�A�h���X�Ɏg�����̃|�C���^�𑫂���memcpy
	memcpy(m_pMappedBuffer + top, &data, sizeof(T));

	// �r���[������Ēl���V�F�[�_�[�ɃA�^�b�`
	D3D12_CONSTANT_BUFFER_VIEW_DESC cbDesc = {};
	cbDesc.BufferLocation = m_pBuffer->GetGPUVirtualAddress() + (UINT64)top * 0x100;
	cbDesc.SizeInBytes = sizeAligned;

	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = m_pHeap->GetHeap()->GetCPUDescriptorHandleForHeapStart();
	cpuHandle.ptr += (UINT64)m_pGraphicsDevice->GetDevice()->GetDescriptorHandleIncrementSize
	(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV) * m_currentUseNumber;

	m_pGraphicsDevice->GetDevice()->CreateConstantBufferView(&cbDesc, cpuHandle);

	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle = m_pHeap->GetHeap()->GetGPUDescriptorHandleForHeapStart();
	gpuHandle.ptr += (UINT64)m_pGraphicsDevice->GetDevice()->GetDescriptorHandleIncrementSize
	(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV) * m_currentUseNumber;

	m_pGraphicsDevice->GetCmdList()->SetGraphicsRootDescriptorTable(descIndex, gpuHandle);

	m_currentUseNumber += useValue;
}