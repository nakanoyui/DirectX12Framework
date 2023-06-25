#pragma once

using Microsoft::WRL::ComPtr;

namespace Math = DirectX::SimpleMath;

/// <summary>
/// �t�@�C���p�X����e�f�B���N�g���܂ł̃p�X���擾
/// </summary>
/// <param name="path">�t�@�C���p�X</param>
/// <returns>�f�B���N�g���p�X</returns>
inline std::string GetDirFromPath(const std::string& path)
{
	const std::string::size_type pos = path.find_last_of('/');
	return (pos == std::string::npos) ? std::string() : path.substr(0, pos + 1);
}