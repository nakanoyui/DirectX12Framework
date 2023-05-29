#pragma once

enum class HeapType
{
	CBVSRVUAV = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
	SAMPLER = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER,
	RTV = D3D12_DESCRIPTOR_HEAP_TYPE_RTV,
	DSV = D3D12_DESCRIPTOR_HEAP_TYPE_DSV,
};

template<typename T>
class Heap
{
public:
	Heap() {}
	~Heap() {}

	/// <summary>
	/// �q�[�v�쐬
	/// </summary>
	/// <param name="pDevice">�O���t�B�b�N�X�f�o�C�X�̃|�C���^</param>
	/// <param name="heapType">�q�[�v�̃^�C�v</param>
	/// <param name="useCount">�g�p��</param>
	/// <returns>����������true</returns>
	bool Create(GraphicsDevice* pDevice, HeapType heapType, T useCount)
	{
		D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};

		heapDesc.Type = static_cast<D3D12_DESCRIPTOR_HEAP_TYPE>(heapType);
		heapDesc.NodeMask = 0;
		heapDesc.NumDescriptors = ComputUseCount(useCount);
		heapDesc.Flags = heapType == HeapType::CBVSRVUAV ?
			D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

		auto hr = pDevice->GetDevice()->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&m_pHeap));

		if (FAILED(hr))
		{
			return false;
		}

		m_useCount = useCount;
		m_incrementSize = pDevice->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		m_pDevice = pDevice;

		return true;
	}

	/// <summary>
	/// CPU���A�h���X��Ԃ�
	/// </summary>
	/// <param name="number">�o�^�ԍ�</param>
	/// <returns>CPU���A�h���X</returns>
	virtual const D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHandle(int number)
	{
		D3D12_CPU_DESCRIPTOR_HANDLE handle = m_pHeap->GetCPUDescriptorHandleForHeapStart();
		handle.ptr += (UINT64)m_incrementSize * number;
		return handle;
	}

	/// <summary>
	/// GPU���A�h���X��Ԃ�
	/// </summary>
	/// <param name="number">�o�^�ԍ�</param>
	/// <returns>GPU���A�h���X</returns>
	virtual const D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle(int number)
	{
		D3D12_GPU_DESCRIPTOR_HANDLE handle = m_pHeap->GetGPUDescriptorHandleForHeapStart();
		handle.ptr += (UINT64)m_incrementSize * number;
		return handle;
	}

protected:
	GraphicsDevice* m_pDevice = nullptr;
	ComPtr<ID3D12DescriptorHeap> m_pHeap = nullptr;
	T m_useCount;
	int m_incrementSize = 0;
	int m_nextRegistNumber = 0;

private:
	UINT ComputUseCount(UINT useCount)
	{
		return useCount;
	}

	UINT ComputUseCount(Math::Vector3 useCount)
	{
		return (UINT)(useCount.x + useCount.y + useCount.z);
	}
};