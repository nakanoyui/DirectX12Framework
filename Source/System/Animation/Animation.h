#pragma once

// アニメーションキー
struct AnimKeyQuaternion
{
	float				m_time = 0;			// 時間
	Math::Quaternion	m_quat;				// クォータニオン
};

// アニメーションキー
struct AnimKeyVector3
{
	float				m_time = 0;			// 時間
	Math::Vector3		m_vec;				// 3Dベクトルデータ
};

// アニメーションデータ
struct AnimationData
{
	std::string			m_name;				// アニメーション名
	float				m_maxTime = 0;		// アニメーション最大時間

	struct Channel
	{
		int			m_nodeOffset = -1;	// 対象モデルノードのOffset値

		// 各チャンネル
		std::vector<AnimKeyVector3>		m_translations;	// 位置キーリスト
		std::vector<AnimKeyQuaternion>	m_rotations;	// 回転キーリスト
		std::vector<AnimKeyVector3>		m_scales;		// 拡縮キーリスト

		void Interpolate(Math::Matrix& rDst, float time);
		bool InterpolateTranslations(Math::Vector3& result, float time);
		bool InterpolateRotations(Math::Quaternion& result, float time);
		bool InterpolateScales(Math::Vector3& result, float time);
	};

	// 全ノード用アニメーションデータ
	std::vector<Channel>	m_channels;
};

class Animator
{
public:
	/// <summary>
	/// アニメーションデータの取得
	/// </summary>
	/// <returns>アニメーションデータ</returns>
	const std::shared_ptr<AnimationData> GetAnimationData()const { return m_spAnimation; }

	/// <summary>
	/// アニメーションのセット
	/// </summary>
	/// <param name="rData">アニメーションデータ</param>
	/// <param name="bLoop">ループ再生か？</param>
	inline void SetAnimation(const std::shared_ptr<AnimationData>& rData, const bool bLoop = true)
	{
		m_spAnimation = rData;
		m_bLoop = bLoop;

		m_time = 0.0f;
	}

	/// <summary>
	/// アニメーションが終了しているか
	/// </summary>
	/// <returns>終了していたらtrue</returns>
	bool IsAnimationEnd() const
	{
		if (m_spAnimation == nullptr) { return true; }
		if (m_time >= m_spAnimation->m_maxTime) { return true; }

		return false;
	}

	// アニメーションの更新
	void AdvanceTime(std::vector<ModelData::Node>& rNodes, float speed = 1.0f);

	// アニメーションのリセット
	void ResetAdvanceTime() { m_time = 0; }

	/// <summary>
	/// 現在のアニメーション時間を取得
	/// </summary>
	/// <returns>現在のアニメーション時間</returns>
	float GetNowAnimationTime()const { return m_time; }

	/// <summary>
	/// 現在のアニメーション時間をセット
	/// </summary>
	/// <param name="nowAnimationTime">現在のアニメーション時間</param>
	void SetNowAnimationTime(float nowAnimationTime) { m_time = nowAnimationTime; }

	/// <summary>
	/// 現在のアニメーションの最大時間を取得
	/// </summary>
	/// <returns>現在のアニメーションの最大時間</returns>
	float GetNowAnimationMaxTime()const { return m_spAnimation->m_maxTime; }

private:

	std::shared_ptr<AnimationData>	m_spAnimation = nullptr;	// 再生するアニメーションデータ

	bool m_bLoop;
	float m_time = 0.0f;
};