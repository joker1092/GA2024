#include <PBR_Shead.fxh>
// Vertex shader
PixelShaderInput main_vs(VertexShaderInput vin)
{
    PixelShaderInput vout;
    
    matrix viewProjectionMatrix = mul(mul(World, View), Projection);
    
    //vout.position = mul(sceneRotationMatrix, float4(vin.position, 1.0)).xyz;
    vout.texcoord = float2(vin.texcoord.x, 1.0 - vin.texcoord.y);
	
    float3x3 TBN = float3x3(vin.tangent, vin.bitangent, vin.normal);
    vout.tangentBasis = mul((float3x3) sceneRotationMatrix, transpose(TBN));

    float4x4 mvpMatrix = mul(viewProjectionMatrix, sceneRotationMatrix);
    float4 worldPos = mul(float4(vin.position, 1.0), World);
    vout.position = worldPos;
    float4 viewPos = mul(worldPos, View);
    float4 projPos = mul(viewPos, Projection);
    
    vout.pixelPosition = projPos;
	//vout.pixelPosition = mul(mvpMatrix, float4(vin.position, 1.0));
    return vout;
}
