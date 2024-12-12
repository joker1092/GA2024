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
//matrix ViewPosMat =
//{
//    1.f, 0.f, 0.f, 0.f, // column 0
//        0.f, 1.f, 0.f, 0.f, // column 1
//        0.f, 0.f, 1.f, 0.f, // column 2
//        vViewPosWorld.x, vViewPosWorld.y, vViewPosWorld.z, 1.f // column 3
//};
//    output.Pos = mul(input.Pos, ViewPosMat);
//    output.Pos = mul(output.Pos, mView);
//    output.Pos = mul(output.Pos, mViewProjection);
//    
//    output.TexCoord = normalize((float3) input.Pos);
//    // or
//    output.TexCoord = (float3) input.Pos;