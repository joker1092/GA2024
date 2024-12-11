#include <PBR_Shead.fxh>

// Pixel shader
float4 main_ps(PixelShaderInput pin) : SV_Target
{
	// Sample input textures to get shading model params.
    float3 albedo = albedoTexture.Sample(defaultSampler, pin.texcoord).rgb;
    float metalness = metalnessTexture.Sample(defaultSampler, pin.texcoord).r;
    float roughness = roughnessTexture.Sample(defaultSampler, pin.texcoord).r;

	// Outgoing light direction (vector from world-space fragment position to the "eye").
    float3 Lo = normalize(eyePosition - pin.position);

	// Get current fragment's normal and transform to world space.
    float3 N = normalize(2.0 * normalTexture.Sample(defaultSampler, pin.texcoord).rgb - 1.0);
    N = normalize(mul(pin.tangentBasis, N));
	
	// Angle between surface normal and outgoing light direction.
    float cosLo = max(0.0, dot(N, Lo));
		
	// Specular reflection vector.
    float3 Lr = 2.0 * cosLo * N - Lo;

	// Fresnel reflectance at normal incidence (for metals use albedo color).
    float3 F0 = lerp(Fdielectric, albedo, metalness);

	// Direct lighting calculation for analytical lights.
    float3 directLighting = 0.0;
    for (uint i = 0; i < NumLights; ++i)
    {
        float3 Li = -lights[i].direction;
        float3 Lradiance = lights[i].radiance;

		// Half-vector between Li and Lo.
        float3 Lh = normalize(Li + Lo);

		// Calculate angles between surface normal and various light vectors.
        float cosLi = max(0.0, dot(N, Li));
        float cosLh = max(0.0, dot(N, Lh));

		// Calculate Fresnel term for direct lighting. 
        float3 F = fresnelSchlick(F0, max(0.0, dot(Lh, Lo))); //�ּҰ� F0 , �ִ밪�� 1.0,1.0,1.0
		// Calculate normal distribution for specular BRDF.
        float D = ndfGGX(cosLh, max(0.01, roughness)); // �����Ͻ� 0 �̵Ǹ� ����0�� �ǹǷ� 0�̸� �ּҰ����
		// Calculate geometric attenuation for specular BRDF.
        float G = gaSchlickGGX(cosLi, cosLo, roughness);

		// Diffuse scattering happens due to light being refracted multiple times by a dielectric medium.
		// Metals on the other hand either reflect or absorb energy, so diffuse contribution is always zero.
		// To be energy conserving we must scale diffuse BRDF contribution based on Fresnel factor & metalness.
		// �ݼӼ��� 1�̸� ħ���� �����Ƿ� ǥ������ �Ͼ�� �ʾ� ǥ������ ������ 0,0,0 ���� ó��
		// �ݼӼ��� 0�̸� �ݻ��� ������ ������ŭ ǥ������ ���� ǥ���� �����ϴ�.
		// �ݼӼ��� 1�ȼ��� �ش�Ǵ� �̼� ǥ���� ������ �ǹ��ϹǷ� ������ ����Ͽ� �߰����� ó���Ѵ�.
        float3 kd = lerp(float3(1, 1, 1) - F, float3(0, 0, 0), metalness);

		// Lambert diffuse BRDF.
		// We don't scale by 1/PI for lighting & material units to be more convenient.
		// See: https://seblagarde.wordpress.com/2012/01/08/pi-or-not-to-pi-in-game-lighting-equation/
        float3 diffuseBRDF = kd * albedo / PI;
       
		
		// Cook-Torrance specular microfacet BRDF.
        float3 specularBRDF = (F * D * G) / max(Epsilon, 4.0 * cosLi * cosLo);
		
		// Total contribution for this light.
        directLighting += (diffuseBRDF + specularBRDF) * Lradiance * cosLi;
    }

	// Ambient lighting (IBL).
    float3 ambientLighting;
    if (useIBL.r > 0)
    {
		// Sample diffuse irradiance at normal direction.
        float3 irradiance = irradianceTexture.Sample(defaultSampler, N).rgb;

		// Calculate Fresnel term for ambient lighting.
		// Since we use pre-filtered cubemap(s) and irradiance is coming from many directions
		// use cosLo instead of angle with light's half-vector (cosLh above).
		// See: https://seblagarde.wordpress.com/2011/08/17/hello-world/
        float3 F = fresnelSchlick(F0, cosLo);

		// Get diffuse contribution factor (as with direct lighting).
        float3 kd = lerp(1.0 - F, 0.0, metalness);

		// Irradiance map contains exitant radiance assuming Lambertian BRDF, no need to scale by 1/PI here either.
        float3 diffuseIBL = kd * albedo * irradiance;

		// Sample pre-filtered specular reflection environment at correct mipmap level.
        uint specularTextureLevels = querySpecularTextureLevels(); //  �ؽ����� �ִ� LOD ������ ���Ѵ�.	
        float3 specularIrradiance = specularTexture.SampleLevel(defaultSampler, Lr, roughness * specularTextureLevels).rgb;
		// �ü�->�븻 �ݻ纤�ͷ� ���ø��Ͽ� ��ĥ��� LOD����� specularIrradiance �� ���Ѵ�.

		// Split-sum approximation factors for Cook-Torrance specular BRDF.
        float2 specularBRDF = specularBRDF_LUT.Sample(spBRDF_Sampler, float2(cosLo, roughness)).rg; // LUT�� ���� �ٻ簪 float2 �� ���Ѵ�. �������ϱ�.

		// Total specular IBL contribution.
        float3 specularIBL = (F0 * specularBRDF.x + specularBRDF.y) * specularIrradiance;

		// Total ambient lighting contribution.
        ambientLighting = diffuseIBL + specularIBL;
    }

//    return float4(directLighting + ambientLighting, 1.0);
 //   return float4(pow(float3(directLighting + ambientLighting), 1.0 / 2.2), 1.0);
    return float4(albedo.rgb, 1.0);

}