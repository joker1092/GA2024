#pragma once
#include "framework.h"
class Scene
{
public:
	Scene();
	virtual ~Scene();

	Scene* pParentScene = nullptr;
	D2D_VECTOR_2F vRelativeScale = { 1,1 };
	float fRelativeRotation = 0;
	D2D_VECTOR_2F vRelativeLcation = { 0,0 };
	D2D1_POINT_2F pCentorPoint = { 0,0 };
	D2D1_MATRIX_3X2_F mInvertCenterMat;
	D2D_MATRIX_3X2_F mRelativeTransform;
	D2D_MATRIX_3X2_F mWorldTransform;

	void UpdateTrasform();
	void SetScale(D2D1_VECTOR_2F Scale) { vRelativeScale = Scale; }
	void SetRotation(float Rotation) { fRelativeRotation = Rotation; }
	void SetLocation(D2D1_VECTOR_2F Location) { vRelativeLcation = Location; }
	void SetParant(Scene* _pParentScene) {pParentScene = _pParentScene;}
	D2D_MATRIX_3X2_F GetWorldMatrix() { return mWorldTransform; }
	D2D1_VECTOR_2F GetWorldLocation()
	{
		D2D1_VECTOR_2F out;
		out.x = mWorldTransform._31;
		out.y = mWorldTransform._32;
		return out;
	}
	//virtual D2D1_VECTOR_2F GetWorldLocation() = 0;
};

 