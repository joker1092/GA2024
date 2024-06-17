#include "Scene.h"

void Scene::UpdateTransform()
{
	mRelativeTransform = D2D1::Matrix3x2F::Scale(
		D2D1::SizeF(vRelativeScale.x, vRelativeScale.y),pCentorPoint) *
		D2D1::Matrix3x2F::Rotation(fRelativeRotation,pCentorPoint) *
		D2D1::Matrix3x2F::Translation(vRelativeLocation.x- pCentorPoint.x, vRelativeLocation.y - pCentorPoint.y);

	if (pParentScene != nullptr)
	{
		mWorldTransform = mRelativeTransform * pParentScene->mWorldTransform;
	}
	else {
		mWorldTransform = mRelativeTransform;
	}
}
