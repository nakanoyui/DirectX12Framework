#pragma once

struct AnimationData;

class ModelData
{
public:

	struct Node
	{
		std::shared_ptr<Mesh>	spMesh;	// メッシュ
		Math::Matrix			m_mLocal;
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

	std::vector<Node>& WorkNodes() { return m_nodes; }

	const std::shared_ptr<AnimationData> GetAnimation(const std::string& animName) const;
	const std::shared_ptr<AnimationData> GetAnimation(UINT index) const;

	std::vector<std::shared_ptr<AnimationData>>& WorkAnimation() { return m_spAnimations; }

private:

	std::vector<Node>		m_nodes;
	std::vector<std::shared_ptr<AnimationData>> m_spAnimations;
};