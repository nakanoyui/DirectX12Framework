#include "Model.h"

#include "ModelLoader.h"

bool ModelData::Load(const std::string& filepath)
{
	ModelLoader modelLoader;

	if (!modelLoader.Load(filepath, *this))
	{
		assert(0 && "ƒ‚ƒfƒ‹‚Ìƒ[ƒh‚É¸”s");
		return false;
	}

	return true;
}

const std::shared_ptr<AnimationData> ModelData::GetAnimation(const std::string& animName) const
{
	for (auto&& anim : m_spAnimations)
	{
		if (anim->m_name == animName)
		{
			return anim;
		}
	}

	return nullptr;
}

const std::shared_ptr<AnimationData> ModelData::GetAnimation(UINT index) const
{
	return index >= m_spAnimations.size() ? nullptr : m_spAnimations[index];
}