#include "inc_SimpleShader.hlsli"

// ’Ç‰Á
Texture2D<float4> g_inputTex : register(t0);

// ’Ç‰Á
SamplerState g_ss : register(s0);

// XV
float4 main(VSOutput In) : SV_TARGET
{
    float4 color = g_inputTex.Sample(g_ss, In.uv);
    
    return color;
}