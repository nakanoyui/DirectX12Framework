#include "Model.h"

#include "ModelLoader.h"

bool ModelData::Load(const std::string& filepath)
{
	ModelLoader modelLoader;

	if (!modelLoader.Load(filepath, m_nodes))
	{
		assert(0 && "モデルのロードに失敗");
		return false;
	}

	return true;
}