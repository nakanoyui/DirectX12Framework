#pragma once

#include "Pipeline/Pipeline.h"
#include "RootSignature/RootSignature.h"

struct RenderingSetting
{
	std::vector<InputLayout> InputLayouts;
	std::vector<DXGI_FORMAT> Formats;
	CullMode CullMode = CullMode::Back;
	BlendMode BlendMode = BlendMode::Alpha;
	PrimitiveTopologyType PrimitiveTopologyType = PrimitiveTopologyType::Triangle;
	bool IsDepth = true;
	bool IsDepthMask = true;
	int RTVCount = 1;
	bool IsWireFrame = false;
};

class Shader
{
public:

	/// <summary>
	/// 作成
	/// </summary>
	/// <param name="pGraphicsDevice">グラフィックスデバイスのポインタ</param>
	/// <param name="filePath">ファイルパス</param>
	/// <param name="renderingSetting">描画設定</param>
	/// <param name="rangeTypes">レンジタイプ</param>
	void Create(GraphicsDevice* pGraphicsDevice, const std::wstring& filePath,
		const RenderingSetting& renderingSetting, const std::vector<RangeType>& rangeTypes);

	/// <summary>
	/// 描画開始
	/// </summary>
	/// <param name="w">横幅</param>
	/// <param name="h">縦幅</param>
	void Begin(int w, int h);

	/// <summary>
	/// メッシュの描画
	/// </summary>
	/// <param name="mesh">メッシュ</param>
	void DrawMesh(const Mesh& mesh);

	/// <summary>
	/// モデルの描画
	/// </summary>
	/// <param name="modelData">モデルデータ</param>
	void DrawModel(const ModelData& modelData);

	/// <summary>
	/// CBVカウント取得
	/// </summary>
	/// <returns>CBVカウント</returns>
	UINT GetCBVCount() const { return m_cbvCount; }

private:

	/// <summary>
	/// シェーダーファイルのロード
	/// </summary>
	/// <param name="filePath">ファイルパス</param>
	void LoadShaderFile(const std::wstring& filePath);

	/// <summary>
	/// マテリアルをセット
	/// </summary>
	/// <param name="material">マテリアル情報</param>
	void SetMaterial(const Material& material);

	GraphicsDevice* m_pDevice = nullptr;

	std::unique_ptr<Pipeline>		m_upPipeline = nullptr;
	std::unique_ptr<RootSignature>	m_upRootSignature = nullptr;

	ID3DBlob* m_pVSBlob = nullptr;		// 頂点シェーダー
	ID3DBlob* m_pHSBlob = nullptr;		// ハルシェーダー
	ID3DBlob* m_pDSBlob = nullptr;		// ドメインシェーダー
	ID3DBlob* m_pGSBlob = nullptr;		// ジオメトリシェーダー
	ID3DBlob* m_pPSBlob = nullptr;		// ピクセルシェーダー

	UINT m_cbvCount = 0;
};