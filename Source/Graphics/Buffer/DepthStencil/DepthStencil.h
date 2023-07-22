#pragma once

enum class DepthStencilFormat
{
	DepthLowQuality = DXGI_FORMAT_R16_TYPELESS,
	DepthHighQuality = DXGI_FORMAT_R32_TYPELESS,
	DepthHighQualityAndStencil = DXGI_FORMAT_R24G8_TYPELESS,
};

class DepthStencil :public Buffer
{
public:

	/// <summary>
	/// 深度テクスチャ生成
	/// </summary>
	/// <param name="pGraphicsDevice">GraphicsDeviceのポインタ</param>
	/// <param name="resolution">解像度</param>
	/// <param name="format">深度テクスチャのフォーマット</param>
	bool Create(GraphicsDevice* pGraphicsDevice, const Math::Vector2& resolution,
		DepthStencilFormat format = DepthStencilFormat::DepthHighQuality);

	/// <summary>
	/// 深度バッファに書き込まれているデータを初期化する関数
	/// </summary>
	void ClearBuffer();

	/// <summary>
	/// DSV番号を取得
	/// </summary>
	/// <returns>DSV番号</returns>
	UINT GetDSVNumber() { return m_dsvNumber; }

private:
	UINT m_dsvNumber = 0;
};