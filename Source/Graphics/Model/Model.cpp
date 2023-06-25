#include "Model.h"

#include "ModelLoader.h"

bool ModelData::Load(const std::string& filepath)
{
	ModelLoader modelLoader;

	if (!modelLoader.Load(filepath, m_nodes))
	{
		assert(0 && "ƒ‚ƒfƒ‹‚Ìƒ[ƒh‚É¸”s");
		return false;
	}

	return true;
}