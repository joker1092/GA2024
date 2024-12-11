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
//	Vector4 LightDirection; // ����
//	Vector4 LightAmbient;   // �ֺ��� ����
//	Vector4 LightDiffuse;   // ���ݻ籤
//	Vector4 LightSpecular;  // ���ݻ籤
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
//	Vector3 position{};		// ���� ��ġ ����.
//	Vector3 normal{};			// ���� �븻 ����.
//	Vector3 tangent{};		// ���� ź��Ʈ ����.
//	Vector3 bitangent{};		// ���� ź��Ʈ ����.
//	Vector2 texcoord{};		// ���� �ؽ��� ��ǥ ����.
//};

struct BoneWeightVertex
{
	Vector3 position{};		// ���� ��ġ ����.
	Vector2 texcoord{};		// ���� �ؽ��� ��ǥ ����.
	Vector3 normal{};			// ���� �븻 ����.
	Vector3 tangent{};

	int BlendIndices[4] = {}; //�ִ� 4���� ������ ����, �����ϴ� ���� �ε����� ������ �ִ� 128��;
	float BlendWeights[4] = {}; //����ġ �� 0~1;

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
	Matrix RelativeTransform; //�θ�� ������ ������� ��ȯ
	Matrix OffsetMatrix;	//�������� �޽��� ��� ��ġ
	std::string Name;		//�� �̸�
	int NumChildren = 0;	//�ڽ��� ��
	std::string ParentBoneName;	//�θ� �� �̸�
	std::vector<std::string> MashNames;	//�ش� ���� ����� �޽� �̸�
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