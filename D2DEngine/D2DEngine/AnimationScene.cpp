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
}

void AnimationScene::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	if (pBitmap==nullptr)
	{
		return;
	}
	MOTION* pMotion = pAnimationAsset->GetMotionInfo(nMotionIndex);
	FRAME_INFO Frame = pMotion->Frames[curFrameIndex];
	//DstRect = D2D1::RectF(0, 0, Frame.Source.right - Frame.Source.left, Frame.Source.bottom - Frame.Source.top);
	SrcRect = Frame.Source;
	pRenderTarget->SetTransform(mWorldTransform);
	pRenderTarget->DrawBitmap(pBitmap, DstRect, 1.f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, SrcRect);

}
