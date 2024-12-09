#include <PBR_Shead.fxh>
// Vertex shader
PixelShaderInput main_vs(VertexShaderInput vin)
{
	PixelShaderInput vout;
	vout.position = mul(sceneRotationMatrix, float4(vin.position, 1.0)).xyz;
	vout.texcoord = float2(vin.texcoord.x, 1.0 - vin.texcoord.y);
	
	float3x3 TBN = float3x3(vin.tangent, vin.bitangent, vin.normal);
	vout.tangentBasis = mul((float3x3) sceneRotationMatrix, transpose(TBN));

	float4x4 mvpMatrix = mul(viewProjectionMatrix, sceneRotationMatrix);
	vout.pixelPosition = mul(mvpMatrix, float4(vin.position, 1.0));
	return vout;
}
//PS_INPUT main(VS_INPUT input)
//{
//    PS_INPUT output = (PS_INPUT) 0;
//    
//    output.Pos = mul(input.Pos, World);
//    output.WorldPos = output.Pos;
//    
//    output.Pos = mul(output.Pos, View);
//    output.Pos = mul(output.Pos, Projection);
//    
//    output.Tex = input.Tex;
//    output.Norm = mul(input.Norm, (float3x3) World);
//    output.Tangent = mul(input.Tangent, (float3x3) World);
//    
//    return output;
//}