#include "AnimationScene.h"

AnimationScene::AnimationScene()
{
}

AnimationScene::~AnimationScene()
{
	pRM->ReleaseAnimationAsset(AnimationFilePath);
}

bool AnimationScene::LoadAnimationAsset(const wchar_t* filePath)
{
	if (pRM->CreateAnimationAssetFromFile(filePath, &pAnimationAsset)==false)
	{
		return false;
	}
	AnimationFilePath = filePath;
	return true;
}

void AnimationScene::SetAnimaitonIndex(int index)
{
	nMotionIndex = index;
}

void AnimationScene::Update(float deltatime)
{
	//std::cout << deltatime << std::endl;
	//std::cout << curFrameIndex << std::endl;
	BitmapScene::Update(deltatime);
	nFrameTime += deltatime;
	MOTION* pMotion = pAnimationAsset->GetMotionInfo(nMotionIndex);
	FRAME_INFO& curFrame = pMotion->Frames[curFrameIndex];
	if (nFrameTime > curFrame.Duration)
	{
		prevFrameIndex = curFrameIndex;
		curFrameIndex++;
		if (pMotion->Frames.size()-1 < curFrameIndex) {
			curFrameIndex = 0;
		}
		//nFrameTime -= curFrame.Duration;
		nFrameTime = 0;
	}
	if (bMiror) {
		mFrameTransform = D2D1::Matrix3x2F::Scale({ -1,1 }) * D2D1::Matrix3x2F::Translation(curFrame.Center.x, curFrame.Center.y);
	}
	else {
		mFrameTransform = D2D1::Matrix3x2F::Scale({ 1,1 }) * D2D1::Matrix3x2F::Translation(curFrame.Center.x * -1, curFrame.Center.y);
	}
}

void AnimationScene::Render(ID2D1RenderTarget* pRenderTarget)
{
	//pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	if (pBitmap == nullptr)
	{
		return;
	}
	MOTION* pMotion = pAnimationAsset->GetMotionInfo(nMotionIndex);
	FRAME_INFO Frame = pMotion->Frames[curFrameIndex];
	SrcRect = Frame.Source;
	DstRect = { 0,0 , Frame.Source.right - Frame.Source.left, Frame.Source.bottom - Frame.Source.top };
	//DstRect = { vRelativeLcation.x,vRelativeLcation.y , vRelativeLcation.x + Frame.Source.right - Frame.Source.left,vRelativeLcation.y + Frame.Source.bottom - Frame.Source.top };
	D2D1_MATRIX_3X2_F transform = mInvertCenterMat * mFrameTransform * mWorldTransform;
	pRenderTarget->SetTransform(transform);
	pRenderTarget->DrawBitmap(pBitmap, DstRect, 1.f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, SrcRect);
}
