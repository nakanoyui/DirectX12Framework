#pragma once

using Microsoft::WRL::ComPtr;

namespace Math = DirectX::SimpleMath;

/// <summary>
/// ファイルパスから親ディレクトリまでのパスを取得
/// </summary>
/// <param name="path">ファイルパス</param>
/// <returns>ディレクトリパス</returns>
inline std::string GetDirFromPath(const std::string& path)
{
	const std::string::size_type pos = path.find_last_of('/');
	return (pos == std::string::npos) ? std::string() : path.substr(0, pos + 1);
}