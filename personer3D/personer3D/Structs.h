#pragma once
#include "framework.h"
#include "../common/Helper.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;


//struct ConstantBuffer
//{
//	DirectX::XMMATRIX mWorld;
//	DirectX::XMMATRIX mView;
//	DirectX::XMMATRIX mProjection;
//};
//
//struct LightBuffer
//{
//	Vector4 LightDirection; // 방향
//	Vector4 LightAmbient;   // 주변광 색상
//	Vector4 LightDiffuse;   // 난반사광
//	Vector4 LightSpecular;  // 정반사광
//};

struct TransformCB
{
	/*DirectX::XMMATRIX viewProjectionMatrix;
	DirectX::XMMATRIX skyProjectionMatrix;*/
	DirectX::XMMATRIX mWorld;
	DirectX::XMMATRIX mView;
	DirectX::XMMATRIX mProjection;
	DirectX::XMMATRIX sceneRotationMatrix;
};

struct ShadingCB
{
	struct
	{
		Vector4 direction;
		Vector4 radiance;
	}lights[3];
	Vector4 eyePosition;
	Vector4 useIBL;
};



//struct Vertex
//{
//	Vector3 position{};		// 정점 위치 정보.
//	Vector3 normal{};			// 정점 노말 정보.
//	Vector3 tangent{};		// 정점 탄젠트 정보.
//	Vector3 bitangent{};		// 정점 탄젠트 정보.
//	Vector2 texcoord{};		// 정점 텍스쳐 좌표 정보.
//};

struct BoneWeightVertex
{
	Vector3 position{};		// 정점 위치 정보.
	Vector2 texcoord{};		// 정점 텍스쳐 좌표 정보.
	Vector3 normal{};			// 정점 노말 정보.
	Vector3 tangent{};

	int BlendIndices[4] = {}; //최대 4개의 본으로 제한, 참조하는 본의 인덱스의 범위는 최대 128개;
	float BlendWeights[4] = {}; //가중치 값 0~1;

	void AddBoneData(int BoneIndex, float Weight)
	{
		assert(BlendWeights[0] == 0.0f || BlendWeights[1] == 0.0f || BlendWeights[2] == 0.0f || BlendWeights[3] == 0.0f);
		for (int i = 0; i < 4; i++)
		{
			if (BlendWeights[i] == 0.0f)
			{
				BlendIndices[i] = BoneIndex;
				BlendWeights[i] = Weight;
				return;
			}
		}
	}
};

//struct Texture
//{
//	ID3D11ShaderResourceView* texture;
//	std::string type;
//	std::string path;
//
//	void Release() {
//		SAFE_RELEASE(texture);
//	}
//};


struct Texture
{
	ID3D11Texture2D* texture;
	ID3D11ShaderResourceView* srv;
	ID3D11UnorderedAccessView* uav;
	UINT width, height;
	UINT levels;
};

struct BoneInfo {
	Matrix RelativeTransform; //부모로 부터의 상대적인 변환
	Matrix OffsetMatrix;	//본에서의 메쉬의 상대 위치
	std::string Name;		//본 이름
	int NumChildren = 0;	//자식의 수
	std::string ParentBoneName;	//부모 본 이름
	std::vector<std::string> MashNames;	//해당 본에 연결된 메쉬 이름
	BoneInfo() {}
	~BoneInfo() { printf_s("%s ~Bone", Name.c_str()); }
	void Set(const aiNode* pNode) {
		Name = std::string(pNode->mName.C_Str());
		RelativeTransform = Matrix(&pNode->mTransformation.a1).Transpose();
		NumChildren = pNode->mNumChildren;
	}
};


struct BoneReference
{
	std::string nodeName;
	Matrix* NodeWorldMatrixPtr;
	int BoneIndex;
};

struct AnimationKey
{
	float m_Time;
	Vector3 m_Position;
	Quaternion m_Rotation;
	Vector3 m_Scaling;
};