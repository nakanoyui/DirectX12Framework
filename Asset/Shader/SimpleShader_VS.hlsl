#include "inc_SimpleShader.hlsli"

VSOutput main(float4 pos : POSITION,
              float2 uv : TEXCOORD,
              float3 normal : NORMAL,
              float4 color : COLOR,
              float3 tangent : TANGENT)
{
    VSOutput Out;
    
    Out.Pos = mul(pos, g_mWorld);
    Out.Pos = mul(Out.Pos, g_mView);
    Out.Pos = mul(Out.Pos, g_mProj);
    
    Out.UV = uv;
    
    Out.Color = color;
    
    Out.Normal = normal;
    
    Out.Tangent = tangent;
    
    return Out;
}