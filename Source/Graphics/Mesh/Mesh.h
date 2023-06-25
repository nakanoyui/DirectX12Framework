#pragma once

#include "MeshData/MeshData.h"

class Texture;

struct MeshFace
{
	UINT Idx[3];
};

struct Material
{
	std::string					Name;						// �}�e���A���̖��O

	std::shared_ptr<Texture>	spBaseColorTex;				// ��{�F�e�N�X�`��
	Math::Vector4				BaseColor = { 1,1,1,1 };	// ��{�F�̃X�P�[�����O�W��(RGBA)

	std::shared_ptr<Texture>	spMetallicRoughnessTex;		// B:������ G:�e��
	float						Metallic = 0.0f;			// �������̃X�P�[�����O�W��
	float						Roughness = 1.0f;			// �e���̃X�P�[�����O�W��

	std::shared_ptr<Texture>	spEmissiveTex;				// ���Ȕ����e�N�X�`��
	Math::Vector3				Emissive = { 0,0,0 };		// ���Ȕ����̃X�P�[�����O�W��(RGB)

	std::shared_ptr<Texture>	spNormalTex;				// �@���e�N�X�`��
};

class Mesh
{
public:

	/// <summary>
	/// �쐬
	/// </summary>
	/// <param name="pGraphicsDevice">�O���t�B�b�N�X�f�o�C�X�̃|�C���^</param>
	/// <param name="vertices">���_���</param>
	/// <param name=" faces">�ʏ��</param>
	/// <param name=" material">�}�e���A�����</param>
	void Create(GraphicsDevice* pGraphicsDevice, const std::vector<MeshVertex>& vertices,
		const std::vector<MeshFace>& faces, const Material& material);

	/// <summary>
	/// �C���X�^���X�`��
	/// </summary>
	/// <param name=" vertexCount">���_��</param>
	void DrawInstanced(UINT vertexCount)const;

	/// <summary>
	/// �C���X�^���X�����擾
	/// </summary>
	/// <returns>�C���X�^���X��</returns>
	UINT GetInstanceCount()const { return m_instanceCount; }

	/// <summary>
	/// �}�e���A���̎擾
	/// </summary>
	/// <returns>�}�e���A�����</returns>
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