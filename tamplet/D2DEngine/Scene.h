#pragma once
#include <d2d1.h>
#include <d2d1_1helper.h>
class Scene
{
public:
	Scene() {};
	virtual ~Scene() {};
	void SetParent(Scene* _pParentScene) { pParentScene = _pParentScene; }
	void SetScale(D2D1_VECTOR_2F Scale) { vRelativeScale=Scale; }
	void SetRotation(float Rotation) { fRelativeRotation = Rotation; }
	void SetLocation(D2D1_VECTOR_2F Location) { vRelativeLocation = Location; }
	void UpdateTransform();
protected:
	Scene* pParentScene =nullptr;
	D2D1_VECTOR_2F vRelativeScale = {1,1};
	float fRelativeRotation =0;
	D2D1_POINT_2F pCentorPoint = { 0,0 };
	D2D1_VECTOR_2F vRelativeLocation = {0,0};
	D2D1_MATRIX_3X2_F mInvertCenterMat;
	D2D1_MATRIX_3X2_F mRelativeTransform;
	D2D1_MATRIX_3X2_F mWorldTransform;
};

