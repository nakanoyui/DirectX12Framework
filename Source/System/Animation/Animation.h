#pragma once

// �A�j���[�V�����L�[
struct AnimKeyQuaternion
{
	float				m_time = 0;			// ����
	Math::Quaternion	m_quat;				// �N�H�[�^�j�I��
};

// �A�j���[�V�����L�[
struct AnimKeyVector3
{
	float				m_time = 0;			// ����
	Math::Vector3		m_vec;				// 3D�x�N�g���f�[�^
};

// �A�j���[�V�����f�[�^
struct AnimationData
{
	std::string			m_name;				// �A�j���[�V������
	float				m_maxTime = 0;		// �A�j���[�V�����ő厞��

	struct Channel
	{
		int			m_nodeOffset = -1;	// �Ώۃ��f���m�[�h��Offset�l

		// �e�`�����l��
		std::vector<AnimKeyVector3>		m_translations;	// �ʒu�L�[���X�g
		std::vector<AnimKeyQuaternion>	m_rotations;	// ��]�L�[���X�g
		std::vector<AnimKeyVector3>		m_scales;		// �g�k�L�[���X�g

		void Interpolate(Math::Matrix& rDst, float time);
		bool InterpolateTranslations(Math::Vector3& result, float time);
		bool InterpolateRotations(Math::Quaternion& result, float time);
		bool InterpolateScales(Math::Vector3& result, float time);
	};

	// �S�m�[�h�p�A�j���[�V�����f�[�^
	std::vector<Channel>	m_channels;
};

class Animator
{
public:
	/// <summary>
	/// �A�j���[�V�����f�[�^�̎擾
	/// </summary>
	/// <returns>�A�j���[�V�����f�[�^</returns>
	const std::shared_ptr<AnimationData> GetAnimationData()const { return m_spAnimation; }

	/// <summary>
	/// �A�j���[�V�����̃Z�b�g
	/// </summary>
	/// <param name="rData">�A�j���[�V�����f�[�^</param>
	/// <param name="bLoop">���[�v�Đ����H</param>
	inline void SetAnimation(const std::shared_ptr<AnimationData>& rData, const bool bLoop = true)
	{
		m_spAnimation = rData;
		m_bLoop = bLoop;

		m_time = 0.0f;
	}

	/// <summary>
	/// �A�j���[�V�������I�����Ă��邩
	/// </summary>
	/// <returns>�I�����Ă�����true</returns>
	bool IsAnimationEnd() const
	{
		if (m_spAnimation == nullptr) { return true; }
		if (m_time >= m_spAnimation->m_maxTime) { return true; }

		return false;
	}

	// �A�j���[�V�����̍X�V
	void AdvanceTime(std::vector<ModelData::Node>& rNodes, float speed = 1.0f);

	// �A�j���[�V�����̃��Z�b�g
	void ResetAdvanceTime() { m_time = 0; }

	/// <summary>
	/// ���݂̃A�j���[�V�������Ԃ��擾
	/// </summary>
	/// <returns>���݂̃A�j���[�V��������</returns>
	float GetNowAnimationTime()const { return m_time; }

	/// <summary>
	/// ���݂̃A�j���[�V�������Ԃ��Z�b�g
	/// </summary>
	/// <param name="nowAnimationTime">���݂̃A�j���[�V��������</param>
	void SetNowAnimationTime(float nowAnimationTime) { m_time = nowAnimationTime; }

	/// <summary>
	/// ���݂̃A�j���[�V�����̍ő厞�Ԃ��擾
	/// </summary>
	/// <returns>���݂̃A�j���[�V�����̍ő厞��</returns>
	float GetNowAnimationMaxTime()const { return m_spAnimation->m_maxTime; }

private:

	std::shared_ptr<AnimationData>	m_spAnimation = nullptr;	// �Đ�����A�j���[�V�����f�[�^

	bool m_bLoop;
	float m_time = 0.0f;
};