#pragma once

#include "MeshData/MeshData.h"

class Texture;

struct MeshFace
{
	UINT Idx[3];
};

struct Material
{
	std::string					Name;						// マテリアルの名前

	std::shared_ptr<Texture>	spBaseColorTex;				// 基本色テクスチャ
	Math::Vector4				BaseColor = { 1,1,1,1 };	// 基本色のスケーリング係数(RGBA)

	std::shared_ptr<Texture>	spMetallicRoughnessTex;		// B:金属製 G:粗さ
	float						Metallic = 0.0f;			// 金属性のスケーリング係数
	float						Roughness = 1.0f;			// 粗さのスケーリング係数

	std::shared_ptr<Texture>	spEmissiveTex;				// 自己発光テクスチャ
	Math::Vector3				Emissive = { 0,0,0 };		// 自己発光のスケーリング係数(RGB)

	std::shared_ptr<Texture>	spNormalTex;				// 法線テクスチャ
};

class Mesh
{
public:

	/// <summary>
	/// 作成
	/// </summary>
	/// <param name="pGraphicsDevice">グラフィックスデバイスのポインタ</param>
	/// <param name="vertices">頂点情報</param>
	/// <param name=" faces">面情報</param>
	/// <param name=" material">マテリアル情報</param>
	void Create(GraphicsDevice* pGraphicsDevice, const std::vector<MeshVertex>& vertices,
		const std::vector<MeshFace>& faces, const Material& material);

	/// <summary>
	/// インスタンス描画
	/// </summary>
	/// <param name=" vertexCount">頂点数</param>
	void DrawInstanced(UINT vertexCount)const;

	/// <summary>
	/// インスタンス数を取得
	/// </summary>
	/// <returns>インスタンス数</returns>
	UINT GetInstanceCount()const { return m_instanceCount; }

	/// <summary>
	/// マテリアルの取得
	/// </summary>
	/// <returns>マテリアル情報</returns>
	const Material& GetMaterial()const { return m_material; }

private:
	GraphicsDevice* m_pDevice = nullptr;
	ComPtr<ID3D12Resource>		m_pVBuffer = nullptr;
	ComPtr<ID3D12Resource>		m_pIBuffer = nullptr;
	D3D12_VERTEX_BUFFER_VIEW	m_vbView;
	D3D12_INDEX_BUFFER_VIEW		m_ibView;

	std::array<Math::Vector3, 3> m_vertices;

	UINT m_instanceCount;
	Material m_material;
};