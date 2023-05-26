#pragma once

class Window
{
public:

	/// <summary>
	/// ウィンドウの作成
	/// </summary>
	/// <param name="clientWidth">横幅</param>
	/// <param name="clientHeight">縦幅</param>
	/// <param name="titleName">タイトル名</param>
	/// <param name="windowClassName">クラス名</param>
	/// <returns>成功したらtrue</returns>
	bool Create(int clientWidth, int clientHeight, const std::wstring& titleName, const std::wstring& windowClassName);

	/// <summary>
	/// ウィンドウメッセージ処理
	/// </summary>
	/// <returns>終了メッセージが来たらfalseが来る</returns>
	bool ProcessMessage();

private:
	HWND	m_hWnd;		// ウィンドウハンドル
};