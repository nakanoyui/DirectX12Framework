#pragma once

class ModelData
{
public:

	struct Node
	{
		std::shared_ptr<Mesh>	spMesh;	// メッシュ
	};

	/// <summary>
	/// モデルのロード
	/// </summary>
	/// <param name="filepath">ファイルパス</param>
	/// <returns>成功したらtrue</returns>
	bool Load(const std::string& filepath);

	/// <summary>
	/// ノードの取得
	/// </summary>
	/// <returns>ノード情報</returns>
	const std::vector<Node>& GetNodes()const { return m_nodes; }

private:

	std::vector<Node>		m_nodes;
};