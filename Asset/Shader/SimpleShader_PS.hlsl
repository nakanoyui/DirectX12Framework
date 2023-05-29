#include "inc_SimpleShader.hlsli"

// 追加
Texture2D<float4> g_inputTex : register(t0);

// 追加
SamplerState g_ss : register(s0);

// 更新
float4 main(VSOutput In) : SV_TARGET
{
    float4 color = g_inputTex.Sample(g_ss, In.uv);
    
    return color;
}