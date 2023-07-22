#pragma once

class RTVHeap;
class CBVSRVUAVHeap;
class CBufferAllocater;
class DSVHeap;
class DepthStencil;

class GraphicsDevice
{
public:

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="hWnd">�E�B���h�E�n���h��</param>
	/// <param name="w">����</param>
	/// <param name="h">�c��</param>
	/// <returns>����������true</returns>
	bool Init(HWND hWnd, int w, int h);

	/// <summary>
	/// �`�揀��
	/// </summary>
	void Prepare();

	/// <summary>
	/// ���(�X���b�v�`�F�C��)�̐؂�ւ�
	/// </summary>
	void ScreenFlip();

	/// <summary>
	/// �R�}���h�L���[�̓����҂�
	/// </summary>
	void WaitForCommandQueue();

	/// <summary>
	/// �f�o�C�X�̎擾
	/// </summary>
	/// <returns>�f�o�C�X�̃|�C���^</returns>
	ID3D12Device8* GetDevice()const { return m_pDevice.Get(); }

	/// <summary>
	/// �R�}���h���X�g�̎擾
	/// </summary>
	/// <returns>�R�}���h���X�g�̃|�C���^</returns>
	ID3D12GraphicsCommandList6* GetCmdList()const { return m_pCmdList.Get(); }

	/// <summary>
	/// CBVSRVUAV�q�[�v�̎擾
	/// </summary>
	/// <returns>CBVSRVUAVHeap�̃|�C���^</returns>
	CBVSRVUAVHeap* GetCBVSRVUAVHeap()const { return m_upCBVSRVUAVHeap.get(); }

	/// <summary>
	/// CBufferAllocater�̎擾
	/// </summary>
	/// <returns>CBufferAllocater�̃|�C���^</returns>
	CBufferAllocater* GetCBufferAllocater()const { return m_upCBufferAllocater.get(); }

	/// <summary>
	/// DSVHeap�̎擾
	/// </summary>
	/// <returns>DSVHeap�̃|�C���^</returns>
	DSVHeap* GetDSVHeap()const { return m_upDSVHeap.get(); }

private:

	/// <summary>
	/// �t�@�N�g���[�̍쐬
	/// </summary>
	/// <returns>����������true</returns>
	bool CreateFactory();

	/// <summary>
	/// �f�o�C�X�̍쐬
	/// </summary>
	/// <returns>����������true</returns>
	bool CreateDevice();

	/// <summary>
	/// �R�}���h���X�g�̍쐬
	/// </summary>
	/// <returns>����������true</returns>
	bool CreateCommandList();

	/// <summary>
	/// �X���b�v�`�F�C���̍쐬
	/// </summary>
	/// <param name="hWnd"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <returns>����������true</returns>
	bool CreateSwapchain(HWND hWnd, int width, int height);

	/// <summary>
	/// �X���b�v�`�F�C��RTV�̍쐬
	/// </summary>
	/// <returns>����������true</returns>
	bool CreateSwapchainRTV();

	/// <summary>
	/// Fence�̍쐬
	/// </summary>
	/// <returns>����������true</returns>
	bool CreateFence();

	/// <summary>
	/// ���\�[�X�Ƃ��Ĉ����ɓn�����o�b�t�@�̈�������ύX����֐�
	/// </summary>
	/// <param name="pResource">�w��o�b�t�@</param>
	/// <param name="before">���݂̏��</param>
	/// <param name="after">�V�������</param>
	void SetResourceBarrier(ID3D12Resource* pResource, D3D12_RESOURCE_STATES before, D3D12_RESOURCE_STATES after);

	/// <summary>
	/// �f�o�b�O���C���[��K�p
	/// </summary>
	void EnableDebugLayer();

	enum class GPUTier
	{
		NVIDIA,
		Amd,
		Intel,
		Arm,
		Qualcomm,
		Kind,
	};

	ComPtr<ID3D12Device8>					m_pDevice = nullptr;
	ComPtr<IDXGIFactory6>					m_pDxgiFactory = nullptr;

	ComPtr<ID3D12CommandAllocator>			m_pCmdAllocator = nullptr;
	ComPtr<ID3D12GraphicsCommandList6>		m_pCmdList = nullptr;
	ComPtr<ID3D12CommandQueue>				m_pCmdQueue = nullptr;

	ComPtr<IDXGISwapChain4>					m_pSwapChain = nullptr;

	std::array<ComPtr<ID3D12Resource>, 2>	m_pSwapchainBuffers;
	std::unique_ptr<RTVHeap>				m_pRTVHeap = nullptr;

	ComPtr<ID3D12Fence>					m_pFence = nullptr;
	UINT64								m_fenceVal = 0;

	std::unique_ptr<RTVHeap>			m_upRTVHeap = nullptr;
	std::unique_ptr<CBVSRVUAVHeap>		m_upCBVSRVUAVHeap = nullptr;
	std::unique_ptr<CBufferAllocater>	m_upCBufferAllocater = nullptr;
	std::unique_ptr<DSVHeap>			m_upDSVHeap = nullptr;
	std::unique_ptr<DepthStencil>		m_upDepthStencil = nullptr;

	GraphicsDevice() {}
	~GraphicsDevice() {}
public:
	static GraphicsDevice& Instance()
	{
		static GraphicsDevice instance;
		return instance;
	}
};