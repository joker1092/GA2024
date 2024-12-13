#include <skybox.fxh>

PixelShaderInput main_vs(float3 position : POSITION)
{
    PixelShaderInput vout;
    float4 p = mul(float4(position, 1.0), World);
    p = mul(p, View);
    p = mul(p, Projection);
    
    p = p.xyww;
    
    vout.localPosition = position;
    vout.pixelPosition = p;
    return vout;
}
