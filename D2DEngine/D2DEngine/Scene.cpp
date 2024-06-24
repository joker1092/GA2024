#include "Scene.h"

Scene::Scene()
{
	mRelativeTransform = mWorldTransform = D2D1::Matrix3x2F::Identity();
}

Scene::~Scene()
{
}

void Scene::UpdateTrasform()
{
	mInvertCenterMat = D2D1::Matrix3x2F::Identity() * D2D1::Matrix3x2F::Translation(pCentorPoint.x, pCentorPoint.y);
	D2D1InvertMatrix(&mInvertCenterMat);

	mRelativeTransform = mInvertCenterMat*D2D1::Matrix3x2F::Scale(D2D1::SizeF(vRelativeScale.x, vRelativeScale.y)) *
		D2D1::Matrix3x2F::Rotation(fRelativeRotation) *
		D2D1::Matrix3x2F::Translation(vRelativeLcation.x, vRelativeLcation.y);
	if (pParentScene!= nullptr)
	{
		D2D1_MATRIX_3X2_F pPrantinvert = pParentScene->mInvertCenterMat;
		D2D1InvertMatrix(&pPrantinvert);
		mWorldTransform = mRelativeTransform * pPrantinvert * pParentScene->mWorldTransform;
	}
	else {
		mWorldTransform = mRelativeTransform;
	}
}

