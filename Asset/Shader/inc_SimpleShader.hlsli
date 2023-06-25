struct VSOutput
{
    float4 Pos : SV_Position;
    float2 UV : TEXCOORD0;
    float3 Normal : NORMAL;
    float3 Tangent : TANGENT;
    float4 Color : COLOR;
};

cbuffer cbCamera : register(b0)
{
    row_major matrix g_mView;
    row_major matrix g_mProj;
}

cbuffer cbWorld : register(b1)
{
    row_major matrix g_mWorld;
}