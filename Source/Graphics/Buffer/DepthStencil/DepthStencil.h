#pragma once

enum class DepthStencilFormat
{
	DepthLowQuality = DXGI_FORMAT_R16_TYPELESS,
	DepthHighQuality = DXGI_FORMAT_R32_TYPELESS,
	DepthHighQualityAndStencil = DXGI_FORMAT_R24G8_TYPELESS,
};

class DepthStencil :public Buffer
{
public:

	/// <summary>
	/// �[�x�e�N�X�`������
	/// </summary>
	/// <param name="pGraphicsDevice">GraphicsDevice�̃|�C���^</param>
	/// <param name="resolution">�𑜓x</param>
	/// <param name="format">�[�x�e�N�X�`���̃t�H�[�}�b�g</param>
	bool Create(GraphicsDevice* pGraphicsDevice, const Math::Vector2& resolution,
		DepthStencilFormat format = DepthStencilFormat::DepthHighQuality);

	/// <summary>
	/// �[�x�o�b�t�@�ɏ������܂�Ă���f�[�^������������֐�
	/// </summary>
	void ClearBuffer();

	/// <summary>
	/// DSV�ԍ����擾
	/// </summary>
	/// <returns>DSV�ԍ�</returns>
	UINT GetDSVNumber() { return m_dsvNumber; }

private:
	UINT m_dsvNumber = 0;
};