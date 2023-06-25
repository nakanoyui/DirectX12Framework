#include "Model.h"

#include "ModelLoader.h"

bool ModelData::Load(const std::string& filepath)
{
	ModelLoader modelLoader;

	if (!modelLoader.Load(filepath, m_nodes))
	{
		assert(0 && "���f���̃��[�h�Ɏ��s");
		return false;
	}

	return true;
}