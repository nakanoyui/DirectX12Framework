#pragma once

class Window
{
public:

	/// <summary>
	/// �E�B���h�E�n���h���̎擾
	/// </summary>
	/// <returns>�E�B���h�E�n���h��</returns>
	HWND GetWndHandle() const { return m_hWnd; }

	/// <summary>
	/// �E�B���h�E�̍쐬
	/// </summary>
	/// <param name="clientWidth">����</param>
	/// <param name="clientHeight">�c��</param>
	/// <param name="titleName">�^�C�g����</param>
	/// <param name="windowClassName">�N���X��</param>
	/// <returns>����������true</returns>
	bool Create(int clientWidth, int clientHeight, const std::wstring& titleName, const std::wstring& windowClassName);

	/// <summary>
	/// �E�B���h�E���b�Z�[�W����
	/// </summary>
	/// <returns>�I�����b�Z�[�W��������false������</returns>
	bool ProcessMessage();

private:
	HWND	m_hWnd;		// �E�B���h�E�n���h��
};