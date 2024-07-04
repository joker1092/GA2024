#pragma once
#include "framework.h"
#include "BitmapScene.h"
#include "AnimationAsset.h"
class AnimationAsset;
struct MOTION;

class AnimationScene : public BitmapScene
{

public:

    AnimationScene();
    virtual ~AnimationScene();

    AnimationAsset* pAnimationAsset = nullptr;
    
    // 인스턴스마다 다른 애니메이션 정보
    MOTION* m_pAnimationInfo = nullptr;	// 현재 애니메이션 프레임 정보
    std::wstring m_strAnimationAssetFilePath;    // 애니메이션 정보 파일 이름
    float m_FrameTime = 0.0f;	// 프레임 진행시간
    int m_FrameIndexCurr = -1;		// 현재 프레임 인덱스
    int m_FrameIndexPrev = -1;		// 이전 프레임 인덱스
    int m_AnimationIndex = -1;	// 현재 애니메이션 인덱스
    D2D1_RECT_F m_SrcRect;		// D2D1Bitmap의 Source 영역
    D2D1_RECT_F m_DstRect;		// RenderTarget의 Destination 영역		

    bool m_bMirror;				// 좌우 반전 여부
    D2D1_MATRIX_3X2_F	m_ImageTransform;	// 반대 방향으로 뒤집기 위한 행렬 Scale.x = -1.0f 

    bool LoadAnimationAsset(const std::wstring strFilePath);
    virtual void Update(float fTimeElapsed);
    //virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
    virtual void Render(ID2D1RenderTarget* pRenderTarget);
    void SetAnimation(int index, bool mirror);
    
};

