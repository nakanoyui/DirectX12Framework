#pragma once

enum class RangeType
{
	CBV,
	SRV,
	UAV,
};

enum class TextureAddressMode
{
	Wrap,
	Clamp,
};

enum class D3D12Filter
{
	Point,
	Linear,
};

class RootSignature
{
public:

	/// <summary>
	/// 作成
	/// </summary>
	/// <param name="pGraphicsDevice">グラフィックスデバイスのポインタ</param>
	/// <param name="rangeTypes">レンジタイプリスト</param>
	/// <param name="cbvCount">CBV数</param>
	void Create(GraphicsDevice* pGraphicsDevice, const std::vector<RangeType>& rangeTypes, UINT& cbvCount);

	/// <summary>
	/// ルートシグネチャの取得
	/// </summary>
	/// <returns>ルートシグネチャのポインタ</returns>
	ID3D12RootSignature* GetRootSignature() { return m_pRootSignature.Get(); }

private:

	/// <summary>
	/// レンジの作成
	/// </summary>
	/// <param name="pRange">レンジのポインタ</param>
	/// <param name="type">レンジタイプ</param>
	/// <param name="count">登録数</param>
	void CreateRange(D3D12_DESCRIPTOR_RANGE& pRange, RangeType type, int count);

	/// <summary>
	/// サンプラーの作成
	/// </summary>
	/// <param name="pSamplerDesc">サンプラーデスクのポインタ</param>
	/// <param name="mode">アドレスモード</param>
	/// <param name="filter">フィルター</param>
	/// <param name="count">使用サンプラー数</param>
	void CreateStaticSampler(D3D12_STATIC_SAMPLER_DESC& samplerDesc, TextureAddressMode mode,
		D3D12Filter filter, int count);

	GraphicsDevice* m_pDevice = nullptr;
	ComPtr<ID3DBlob> m_pRootBlob = nullptr;
	ComPtr<ID3D12RootSignature> m_pRootSignature = nullptr;
};