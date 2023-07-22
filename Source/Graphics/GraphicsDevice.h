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
	/// 初期化
	/// </summary>
	/// <param name="hWnd">ウィンドウハンドル</param>
	/// <param name="w">横幅</param>
	/// <param name="h">縦幅</param>
	/// <returns>成功したらtrue</returns>
	bool Init(HWND hWnd, int w, int h);

	/// <summary>
	/// 描画準備
	/// </summary>
	void Prepare();

	/// <summary>
	/// 画面(スワップチェイン)の切り替え
	/// </summary>
	void ScreenFlip();

	/// <summary>
	/// コマンドキューの同期待ち
	/// </summary>
	void WaitForCommandQueue();

	/// <summary>
	/// デバイスの取得
	/// </summary>
	/// <returns>デバイスのポインタ</returns>
	ID3D12Device8* GetDevice()const { return m_pDevice.Get(); }

	/// <summary>
	/// コマンドリストの取得
	/// </summary>
	/// <returns>コマンドリストのポインタ</returns>
	ID3D12GraphicsCommandList6* GetCmdList()const { return m_pCmdList.Get(); }

	/// <summary>
	/// CBVSRVUAVヒープの取得
	/// </summary>
	/// <returns>CBVSRVUAVHeapのポインタ</returns>
	CBVSRVUAVHeap* GetCBVSRVUAVHeap()const { return m_upCBVSRVUAVHeap.get(); }

	/// <summary>
	/// CBufferAllocaterの取得
	/// </summary>
	/// <returns>CBufferAllocaterのポインタ</returns>
	CBufferAllocater* GetCBufferAllocater()const { return m_upCBufferAllocater.get(); }

	/// <summary>
	/// DSVHeapの取得
	/// </summary>
	/// <returns>DSVHeapのポインタ</returns>
	DSVHeap* GetDSVHeap()const { return m_upDSVHeap.get(); }

private:

	/// <summary>
	/// ファクトリーの作成
	/// </summary>
	/// <returns>成功したらtrue</returns>
	bool CreateFactory();

	/// <summary>
	/// デバイスの作成
	/// </summary>
	/// <returns>成功したらtrue</returns>
	bool CreateDevice();

	/// <summary>
	/// コマンドリストの作成
	/// </summary>
	/// <returns>成功したらtrue</returns>
	bool CreateCommandList();

	/// <summary>
	/// スワップチェインの作成
	/// </summary>
	/// <param name="hWnd"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <returns>成功したらtrue</returns>
	bool CreateSwapchain(HWND hWnd, int width, int height);

	/// <summary>
	/// スワップチェインRTVの作成
	/// </summary>
	/// <returns>成功したらtrue</returns>
	bool CreateSwapchainRTV();

	/// <summary>
	/// Fenceの作成
	/// </summary>
	/// <returns>成功したらtrue</returns>
	bool CreateFence();

	/// <summary>
	/// リソースとして引数に渡したバッファの扱いをを変更する関数
	/// </summary>
	/// <param name="pResource">指定バッファ</param>
	/// <param name="before">現在の状態</param>
	/// <param name="after">新しい状態</param>
	void SetResourceBarrier(ID3D12Resource* pResource, D3D12_RESOURCE_STATES before, D3D12_RESOURCE_STATES after);

	/// <summary>
	/// デバッグレイヤーを適用
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