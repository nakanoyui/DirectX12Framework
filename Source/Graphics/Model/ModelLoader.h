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
	/// モデルのロード
	/// </summary>
	/// <param name="filepath">ファイルパス</param>
	/// <param name="nodes">ノード情報</param>
	/// <returns>成功したらtrue</returns>
	bool Load(std::string filepath, std::vector<ModelData::Node>& nodes);

private:

	/// <summary>
	/// 解析
	/// </summary>
	/// <param name="pScene">モデルシーンのポインタ</param>
	/// <param name="pMesh">メッシュのポインタ</param>
	/// <param name="pMaterial">マテリアルのポインタ</param>
	/// <param name="dirPath">ディレクトリパス</param>
	/// <returns>メッシュポインタ</returns>
	std::shared_ptr<Mesh> Parse(const aiScene* pScene, const aiMesh* pMesh,
		const aiMaterial* pMaterial, const std::string& dirPath);

	/// <summary>
	/// マテリアルの解析
	/// </summary>
	/// <param name="pMaterial">マテリアルのポインタ</param>
	/// <param name="dirPath">ディレクトリパス</param>
	/// <returns>マテリアル情報</returns>
	const Material ParseMaterial(const aiMaterial* pMaterial, const std::string& dirPath);
};