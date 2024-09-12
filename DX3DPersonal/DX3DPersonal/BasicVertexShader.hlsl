#include <Shared.fxh>
// ¡§¡° ºŒ¿Ã¥ı.


PS_INPUT main(float4 pos : POSITION, float4 color : COLOR)
{
    PS_INPUT output;
    
    float4 worldPos = mul(pos, World);
    float4 viewPos = mul(worldPos, View);
    float4 projPos = mul(viewPos, Projection);
    
    output.pos = projPos;
    output.color = color;
    return output;
}