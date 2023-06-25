#include "inc_SimpleShader.hlsli"

Texture2D g_diffuseTex : register(t0);              // Diffuse�e�N�X�`��
Texture2D g_normalTex : register(t1);               // �@���e�N�X�`��
Texture2D g_RoughnessMetallicTex : register(t2);    // RoughnessMetallic�}�b�v
Texture2D g_emissiveTex : register(t3);             // Emissive�e�N�X�`��

SamplerState g_ss : register(s0);

float4 main(VSOutput In) : SV_TARGET
{
    float4 color = g_diffuseTex.Sample(g_ss, In.UV);
    
    return color;
}