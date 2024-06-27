#pragma once
#include "framework.h"
#include "BitmapScene.h"
#include "AnimationAsset.h"
class AnimationScene :
    public BitmapScene
{
    AnimationAsset* pAnimationAsset;
    
    int prevFrameIndex = 0;
    int nMotionIndex = 0;
    float nFrameTime = 0;
    D2D1_RECT_F SrcRect;
    D2D1_RECT_F DstRect;
    
    
    D2D1_MATRIX_3X2_F mFrameTransform;
    std::wstring AnimationFilePath;

public:
    AnimationScene();
    virtual ~AnimationScene();
    bool bMiror;
    int curFrameIndex = 0;
    void SetMiror(bool miror) { bMiror = miror; }
    bool LoadAnimationAsset(const wchar_t* filePath);
    void SetAnimaitonIndex(int index);
    void Update(float deltatime);
    void Render(ID2D1HwndRenderTarget* pRenderTarget);
    void SetDstRect(D2D1_RECT_F rect) { DstRect = rect; }
};

