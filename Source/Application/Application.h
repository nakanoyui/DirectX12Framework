#pragma once

#include "../System/Window/Window.h"
#include "../Pch.h"

class Application
{
public:

	/// <summary>
	/// �A�v���P�[�V�������s
	/// </summary>
	void Execute();

private:

	/// <summary>
	/// .dll�̃f�B���N�g���̃Z�b�g�ƃ��[�h���s��
	/// </summary>
	void SetDirectoryAndLoadDll();

	Window m_window;

	Application() {}
	~Application() {}
public:
	static Application& Instance()
	{
		static Application instance;
		return instance;
	}
};