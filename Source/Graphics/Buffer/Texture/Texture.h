#pragma once

class Texture :public Buffer
{
public:

	/// <summary>
	/// �e�N�X�`���̃��[�h
	/// </summary>
	/// <param name="pGraphicsDevice">�O���t�B�b�N�X�f�o�C�X�̃|�C���^</param>
	/// <param name="filePath">�t�@�C���p�X</param>
	/// <returns>���[�h������������true</returns>
	bool Load(GraphicsDevice* pGraphicsDevice, const std::string& filePath);

	/// <summary>
	/// �V�F�[�_�[���\�[�X�Ƃ��ăZ�b�g
	/// </summary>
	/// <param name="index">�C���f�b�N�X</param>
	void Set(int index);

	/// <summary>
	/// SRV�ԍ����擾
	/// </summary>
	/// <returns>SRV�ԍ�</returns>
	int GetSRVNumber() { return m_srvNumber; }

private:
	int m_srvNumber = 0;
};