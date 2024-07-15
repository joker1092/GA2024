#include "AnimationScene.h"
#include "D2DRender.h"

class D2DRender;
class GameObject;
AnimationScene::AnimationScene()
{
}

AnimationScene::~AnimationScene()
{
	if (pAnimationAsset)
	{
		pRM->ReleaseAnimationAsset(m_strAnimationAssetFilePath);
		pAnimationAsset = nullptr;
	}
	
}

bool AnimationScene::LoadAnimationAsset(const std::wstring strFilePath)
{
	if (pRM->CreateAnimationAssetFromFile(strFilePath, &pAnimationAsset)==false)
	{
		return false;
	}
	m_strAnimationAssetFilePath = strFilePath;
	return true;
}

void AnimationScene::Update(float deltatime)
{
	BitmapScene::Update(deltatime);
	//assert(m_pAnimationAsset != nullptr);  // asset이 없으면 debug모드에서 멈춤
	if (pAnimationAsset == nullptr)
		return;

	/*std::cout << isEndMotion << std::endl;*/

	const FRAME_INFO& Frame = m_pAnimationInfo->Frames[m_FrameIndexCurr];
	size_t MaxFrameCount = m_pAnimationInfo->Frames.size();

	///////////////     
	// m_FrameTime에 fTimeElapsed을 누적시켜  Frame.Duration보다 크면 
	// m_FrameIndexCurr를 증가시키고 m_FrameTime을 0으로 초기화한다.
	// 일단 루프만 가정하고 처리한다.
	////////////////
	m_FrameTime+=deltatime;
	if (m_FrameTime > Frame.Duration)
	{
		m_FrameIndexPrev = m_FrameIndexCurr;
		m_FrameIndexCurr++;
		if (m_pAnimationInfo->Frames.size() - 1 < m_FrameIndexCurr) {
			m_FrameIndexCurr = 0;
			isEndMotion = true;
		}
		//nFrameTime -= curFrame.Duration;
		m_FrameTime = 0;
	}



	m_SrcRect = Frame.Source;
	m_DstRect = { 0,0,m_SrcRect.right - m_SrcRect.left,m_SrcRect.bottom - m_SrcRect.top };

	if (m_bMirror) //x 축 스케일은 좌우 반전 , Translation 은 출력할 이미지의 원점 정보
	{
		m_ImageTransform = D2D1::Matrix3x2F::Scale(-1.0f, 1.0f, D2D1::Point2F(0, 0)) *
			D2D1::Matrix3x2F::Translation(Frame.Center.x, Frame.Center.y);
	}
	else
	{
		m_ImageTransform = D2D1::Matrix3x2F::Scale(1.0f, 1.0f, D2D1::Point2F(0, 0)) *
			D2D1::Matrix3x2F::Translation(Frame.Center.x * -1, Frame.Center.y);
	}
}

//void AnimationScene::Render(ID2D1HwndRenderTarget* pRenderTarget)
//{
//	if (m_pAnimationInfo == nullptr)
//		return;
//
//	D2D1_MATRIX_3X2_F Transform = m_ImageTransform * m_WorldTransform * pD2DRender->m_CameraTransform;
//	pRenderTarget->SetTransform(Transform);
//	pRenderTarget->DrawBitmap(pBitmap, m_DstRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_SrcRect);
//}

void AnimationScene::Render(ID2D1RenderTarget* pRenderTarget)
{
	if (m_pAnimationInfo == nullptr)
		return;
	width = m_DstRect.right- m_DstRect.left;
	height= m_DstRect.bottom- m_DstRect.top;

	D2D1_MATRIX_3X2_F m_ScreenTransform =D2D1::Matrix3x2F::Scale(1.0f, -1.0f)* D2D1::Matrix3x2F::Translation(0.0f, D2DRender::Instance->GetClientSize().height);
	D2D1_MATRIX_3X2_F Transform = D2D1::Matrix3x2F::Scale(1.0f, -1.0f) * m_ImageTransform * m_WorldTransform * pD2DRender->m_CameraTransform * m_ScreenTransform;
	pRenderTarget->SetTransform(Transform);
	pRenderTarget->DrawBitmap(pBitmap, m_DstRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_SrcRect);
	pRenderTarget->DrawRectangle(m_DstRect, D2DRender::Instance->getBrush());
}

void AnimationScene::SetAnimation(int index, bool mirror)
{
	//assert(m_pAnimationAsset != nullptr);
	if (pAnimationAsset == nullptr)
		return;

	MOTION* pFound = pAnimationAsset->GetMotionInfo(index);
	if (pFound == nullptr)
		return;

	m_pAnimationInfo = pFound;
	m_bMirror = mirror;
	m_FrameIndexCurr = 0;
	m_FrameIndexPrev = 0;
	m_FrameTime = 0.0f;
	isEndMotion = false;
}

void AnimationScene::SetAnimationIndex(int index)
{
	//assert(m_pAnimationAsset != nullptr);
	if (pAnimationAsset == nullptr)
		return;

	MOTION* pFound = pAnimationAsset->GetMotionInfo(index);
	if (pFound == nullptr)
		return;

	m_pAnimationInfo = pFound;
	m_FrameIndexCurr = 0;
	m_FrameIndexPrev = 0;
	m_FrameTime = 0.0f;
	isEndMotion = false;
}
