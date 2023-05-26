#pragma once

class RTVHeap;

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
	/// ���(�X���b�v�`�F�C��)�̐؂�ւ�
	/// </summary>
	void ScreenFlip();

	/// <summary>
	/// �R�}���h�L���[�̓����҂�
	/// </summary>
	void WaitForCommandQueue();

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

	//? �ǉ�
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

	GraphicsDevice() {}
	~GraphicsDevice() {}
public:
	static GraphicsDevice& Instance()
	{
		static GraphicsDevice instance;
		return instance;
	}
};