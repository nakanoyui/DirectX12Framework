#pragma once

// メッシュの頂点情報
struct MeshVertex
{
	Math::Vector3 Position;
	Math::Vector2 UV;
	Math::Vector3 Normal;
	UINT Color = 0xFFFFFFFF;
	Math::Vector3 Tangent;
};