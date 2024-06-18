#include "AnimationInstance.h"

bool AnimationInstance::SetAnimationAsset(const wchar_t* FilePath, AnimationAsset::State state)
{
	return (!pAnimationAsset->setAnimation(FilePath,state)) ;
}

void AnimationInstance::Update(float deltaTime)
{
	progressTime += deltaTime;
	float time = 0;
	int index = 0;
	std::vector<FRAME_INFO > animation = pAnimationAsset->Animations[animationIndex];
	for (const FRAME_INFO& frame : animation)
	{
		time += frame.renderTime;
		if (time > progressTime) break;
		index++;
	}
	frameIndex = index;
	FRAME_INFO info = animation[frameIndex];
	srcRect = info.sourceRect;
	dstRect = { 0,0,srcRect.right - srcRect.left,srcRect.bottom - srcRect.top };
	D2D1_MATRIX_3X2_F CenterMat = D2D1::Matrix3x2F::Identity() * D2D1::Matrix3x2F::Translation(info.pCenter.x, info.pCenter.y);
	D2D1InvertMatrix(&CenterMat);
	transform= CenterMat *D2D1::Matrix3x2F::Scale(
		D2D1::SizeF(1,1)) *
		D2D1::Matrix3x2F::Rotation(0) *
		D2D1::Matrix3x2F::Translation(position.x, position.y);
}

void AnimationInstance::Render(ID2D1RenderTarget* pRenderTarget)
{
	pRenderTarget->SetTransform(transform);
	pRenderTarget->DrawBitmap(pAnimationAsset->pBitmap, dstRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, srcRect);
}

bool AnimationInstance::SetAnimationIndex(int index)
{
	FRAME_INFO animation0 = pAnimationAsset->Animations[animationIndex][0];
	if (animation0.renderTime == 0)
	{
		return false;
	}
	else {
		animationIndex = index;
		return true;
	}
}
