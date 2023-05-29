#pragma once

class Texture
{
public:

	/// <summary>
	/// テクスチャのロード
	/// </summary>
	/// <param name="pGraphicsDevice">グラフィックスデバイスのポインタ</param>
	/// <param name="filePath">ファイルパス</param>
	/// <returns>ロードが成功したらtrue</returns>
	bool Load(GraphicsDevice* pGraphicsDevice, const std::string& filePath);

	/// <summary>
	/// シェーダーリソースとしてセット
	/// </summary>
	/// <param name="index">インデックス</param>
	void Set(int index);

	/// <summary>
	/// SRV番号を取得
	/// </summary>
	/// <returns>SRV番号</returns>
	int GetSRVNumber() { return m_srvNumber; }

private:
	GraphicsDevice* m_pDevice = nullptr;

	ComPtr<ID3D12Resource> m_pBuffer = nullptr;
	int m_srvNumber = 0;
};