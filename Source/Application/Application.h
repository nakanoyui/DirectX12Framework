#pragma once

#include "../System/Window/Window.h"
#include "../Pch.h"

class Application
{
public:

	/// <summary>
	/// �A�v���P�[�V�������s
	/// </summary>
	void Excute();

private:
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