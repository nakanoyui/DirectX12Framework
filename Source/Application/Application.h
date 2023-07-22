#pragma once

#include "../System/Window/Window.h"
#include "../Pch.h"

class Application
{
public:

	/// <summary>
	/// アプリケーション実行
	/// </summary>
	void Execute();

private:

	/// <summary>
	/// .dllのディレクトリのセットとロードを行う
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