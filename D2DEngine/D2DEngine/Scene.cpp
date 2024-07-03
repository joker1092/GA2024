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
	mInvertCenterMat = D2D1::Matrix3x2F::Translation(-pCentorPoint.x, -pCentorPoint.y);
	/*mInvertCenterMat = D2D1::Matrix3x2F::Translation(-pCentorPoint.x, -pCentorPoint.y);

	mRelativeTransform = mInvertCenterMat*D2D1::Matrix3x2F::Scale(D2D1::SizeF(vRelativeScale.x, vRelativeScale.y)) *
		D2D1::Matrix3x2F::Rotation(fRelativeRotation) *
		D2D1::Matrix3x2F::Translation(vRelativeLcation.x, vRelativeLcation.y);*/
	mRelativeTransform= D2D1::Matrix3x2F::Scale(vRelativeScale.x, vRelativeScale.y) *
		D2D1::Matrix3x2F::Rotation(fRelativeRotation) *
		D2D1::Matrix3x2F::Translation(vRelativeLcation.x, vRelativeLcation.y);
	if (pParentScene!= nullptr)
	{
		mWorldTransform = mRelativeTransform  * pParentScene->mWorldTransform;
	}
	else {
		mWorldTransform = mRelativeTransform;
	}
}

