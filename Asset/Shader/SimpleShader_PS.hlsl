#include "inc_SimpleShader.hlsli"

Texture2D g_diffuseTex : register(t0);              // Diffuseテクスチャ
Texture2D g_normalTex : register(t1);               // 法線テクスチャ
Texture2D g_RoughnessMetallicTex : register(t2);    // RoughnessMetallicマップ
Texture2D g_emissiveTex : register(t3);             // Emissiveテクスチャ

SamplerState g_ss : register(s0);

float4 main(VSOutput In) : SV_TARGET
{
    float4 color = g_diffuseTex.Sample(g_ss, In.UV);
    
    return color;
}