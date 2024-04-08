#include "Animation.h"

// �񕪒T���ŁA�w�莞�Ԃ��玟�̔z��v�f��KeyIndex�����߂�֐�
template<class T>
int BinarySearchNextAnimKey(const std::vector<T>& list, float time)
{
	int low = 0;
	int high = (int)list.size();
	while (low < high)
	{
		int mid = (low + high) / 2;
		float midTime = list[mid].m_time;

		if (midTime <= time) low = mid + 1;
		else high = mid;
	}
	return low;
}

void Animator::ProgressTime(std::vector<ModelData::Node>& rNodes, float speed)
{
	if (!m_spAnimation) { return; }

	UINT idx = 0;

	// �S�ẴA�j���[�V�����m�[�h�i���f���̍s����Ԃ�����j�̍s���Ԃ����s����
	for (auto& animChannel : m_spAnimation->m_channels)
	{
		auto prev = rNodes[idx].m_mLocal;

		// �A�j���[�V�����f�[�^�ɂ��s����
		animChannel.Interpolate(rNodes[idx].m_mLocal, m_time);

		prev = rNodes[idx].m_mLocal;

		++idx;
	}

	// �A�j���[�V�����̃t���[����i�߂�
	m_time += speed;

	// �A�j���[�V�����f�[�^�̍Ō�̃t���[���𒴂�����
	if (m_time >= m_spAnimation->m_maxTime)
	{
		if (m_bLoop)
		{
			// �A�j���[�V�����̍ŏ��ɖ߂�i���[�v������
			m_time = 0.0f;
		}
		else
		{
			m_time = m_spAnimation->m_maxTime;
		}
	}
}

void AnimationData::Channel::Interpolate(Math::Matrix& rDst, float time)
{
	// �x�N�^�[�ɂ��g�k���
	bool isChange = false;
	Math::Matrix scale;
	Math::Vector3 resultVec;
	if (InterpolateScales(resultVec, time))
	{
		scale = scale.CreateScale(resultVec);
		isChange = true;
	}

	// �N�H�^�j�I���ɂ���]���
	Math::Matrix rotate;
	Math::Quaternion resultQuat;
	if (InterpolateRotations(resultQuat, time))
	{
		rotate = rotate.CreateFromQuaternion(resultQuat);
		isChange = true;
	}

	// �x�N�^�[�ɂ����W���
	Math::Matrix trans;
	if (InterpolateTranslations(resultVec, time))
	{
		trans = trans.CreateTranslation(resultVec);
		isChange = true;
	}

	if (isChange)
	{
		rDst = scale * rotate * trans;
	}
}

bool AnimationData::Channel::InterpolateTranslations(Math::Vector3& result, float time)
{
	if (m_translations.size() == 0)return false;

	// �L�[�ʒu����
	UINT keyIdx = BinarySearchNextAnimKey(m_translations, time);

	// �擪�̃L�[�Ȃ�A�擪�̃f�[�^��Ԃ�
	if (keyIdx == 0) {
		result = m_translations.front().m_vec;
		return true;
	}
	// �z��O�̃L�[�Ȃ�A�Ō�̃f�[�^��Ԃ�
	else if (keyIdx >= m_translations.size()) {
		result = m_translations.back().m_vec;
		return true;
	}
	// ����ȊO(���Ԃ̎���)�Ȃ�A���̎��Ԃ̒l���Ԍv�Z�ŋ��߂�
	else {
		auto& prev = m_translations[keyIdx - 1];	// �O�̃L�[
		auto& next = m_translations[keyIdx];		// ���̃L�[
		// �O�̃L�[�Ǝ��̃L�[�̎��Ԃ���A0�`1�Ԃ̎��Ԃ����߂�
		float f = (time - prev.m_time) / (next.m_time - prev.m_time);
		// ���
		result = DirectX::XMVectorLerp(
			prev.m_vec,
			next.m_vec,
			f
		);
	}

	return true;
}

bool AnimationData::Channel::InterpolateRotations(Math::Quaternion& result, float time)
{
	if (m_rotations.size() == 0)return false;

	// �L�[�ʒu����
	UINT keyIdx = BinarySearchNextAnimKey(m_rotations, time);
	// �擪�̃L�[�Ȃ�A�擪�̃f�[�^��Ԃ�
	if (keyIdx == 0) {
		result = m_rotations.front().m_quat;
	}
	// �z��O�̃L�[�Ȃ�A�Ō�̃f�[�^��Ԃ�
	else if (keyIdx >= m_rotations.size()) {
		result = m_rotations.back().m_quat;
	}
	// ����ȊO(���Ԃ̎���)�Ȃ�A���̎��Ԃ̒l���Ԍv�Z�ŋ��߂�
	else {
		auto& prev = m_rotations[keyIdx - 1];	// �O�̃L�[
		auto& next = m_rotations[keyIdx];		// ���̃L�[
		// �O�̃L�[�Ǝ��̃L�[�̎��Ԃ���A0�`1�Ԃ̎��Ԃ����߂�
		float f = (time - prev.m_time) / (next.m_time - prev.m_time);
		// ���
		result = DirectX::XMQuaternionSlerp(
			prev.m_quat,
			next.m_quat,
			f
		);
	}

	return true;
}

bool AnimationData::Channel::InterpolateScales(Math::Vector3& result, float time)
{
	if (m_scales.size() == 0)return false;

	// �L�[�ʒu����
	UINT keyIdx = BinarySearchNextAnimKey(m_scales, time);

	// �擪�̃L�[�Ȃ�A�擪�̃f�[�^��Ԃ�
	if (keyIdx == 0) {
		result = m_scales.front().m_vec;
		return true;
	}
	// �z��O�̃L�[�Ȃ�A�Ō�̃f�[�^��Ԃ�
	else if (keyIdx >= m_scales.size()) {
		result = m_scales.back().m_vec;
		return true;
	}
	// ����ȊO(���Ԃ̎���)�Ȃ�A���̎��Ԃ̒l���Ԍv�Z�ŋ��߂�
	else {
		auto& prev = m_scales[keyIdx - 1];	// �O�̃L�[
		auto& next = m_scales[keyIdx];		// ���̃L�[
		// �O�̃L�[�Ǝ��̃L�[�̎��Ԃ���A0�`1�Ԃ̎��Ԃ����߂�
		float f = (time - prev.m_time) / (next.m_time - prev.m_time);
		// ���
		result = DirectX::XMVectorLerp(
			prev.m_vec,
			next.m_vec,
			f
		);
	}

	return true;
}
