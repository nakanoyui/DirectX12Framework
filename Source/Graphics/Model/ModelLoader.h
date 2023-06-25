#pragma once

#ifdef _DEBUG
#pragma comment(lib,"assimp-vc143-mtd.lib")
#else
#pragma comment(lib,"assimp-vc143-mt.lib")
#endif

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Model.h"

class ModelLoader
{
public:

	/// <summary>
	/// ���f���̃��[�h
	/// </summary>
	/// <param name="filepath">�t�@�C���p�X</param>
	/// <param name="nodes">�m�[�h���</param>
	/// <returns>����������true</returns>
	bool Load(std::string filepath, std::vector<ModelData::Node>& nodes);

private:

	/// <summary>
	/// ���
	/// </summary>
	/// <param name="pScene">���f���V�[���̃|�C���^</param>
	/// <param name="pMesh">���b�V���̃|�C���^</param>
	/// <param name="pMaterial">�}�e���A���̃|�C���^</param>
	/// <param name="dirPath">�f�B���N�g���p�X</param>
	/// <returns>���b�V���|�C���^</returns>
	std::shared_ptr<Mesh> Parse(const aiScene* pScene, const aiMesh* pMesh,
		const aiMaterial* pMaterial, const std::string& dirPath);

	/// <summary>
	/// �}�e���A���̉��
	/// </summary>
	/// <param name="pMaterial">�}�e���A���̃|�C���^</param>
	/// <param name="dirPath">�f�B���N�g���p�X</param>
	/// <returns>�}�e���A�����</returns>
	const Material ParseMaterial(const aiMaterial* pMaterial, const std::string& dirPath);
};