#include <skybox.fxh>

float4 main_ps(PixelShaderInput pin) : SV_Target
{
    float3 envVector = normalize(pin.localPosition);
    return envTexture.SampleLevel(defaultSampler, envVector, 0);
    
    //return float4(envVector, 0.0);
    
    //return float4(1.0f, 1.0f, 1.0f, 0.0);

}