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
	nFrameTime += deltatime;
	MOTION* pMotion = pAnimationAsset->GetMotionInfo(nMotionIndex);
	FRAME_INFO curFrame = pMotion->Frames[curFrameIndex];
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
	
	BitmapScene::Update();
}

void AnimationScene::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	if (pBitmap==nullptr)
	{
		return;
	}
	MOTION* pMotion = pAnimationAsset->GetMotionInfo(nMotionIndex);
	FRAME_INFO Frame = pMotion->Frames[curFrameIndex];
	SrcRect = Frame.Source;
	DstRect = { vRelativeLcation.x,vRelativeLcation.y , vRelativeLcation.x + Frame.Source.right - Frame.Source.left,vRelativeLcation.y + Frame.Source.bottom - Frame.Source.top };
	pRenderTarget->SetTransform(mWorldTransform);
	pRenderTarget->DrawBitmap(pBitmap, DstRect, 1.f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, SrcRect);
}
