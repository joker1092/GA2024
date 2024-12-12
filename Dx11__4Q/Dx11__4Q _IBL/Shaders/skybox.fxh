cbuffer TransformConstants : register(b0)
{
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
    float4x4 sceneRotationMatrix;
};

struct PixelShaderInput
{
    float3 localPosition : POSITION;
    float4 pixelPosition : SV_POSITION;
};

TextureCube envTexture : register(t0);
SamplerState defaultSampler : register(s0);
