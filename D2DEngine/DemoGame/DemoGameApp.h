#pragma once
#include "../D2DEngine/WinGameApp.h"
#include "../D2DEngine/Scene.h"
#include "../D2DEngine/BitmapScene.h"
#include "../D2DEngine/AnimationScene.h"
#include <random>
class DemoGameApp :public WinGameApp
{
    /*BitmapScene Sun;
    BitmapScene Earth;
    BitmapScene Moon;*/
    AnimationScene bg;
    AnimationScene player;
    AnimationScene player2;
    std::vector<AnimationScene*> vObjList;

public:
    D2D1_VECTOR_2F position;
    //float rotate = 0;
    virtual void Initialize(HINSTANCE hInstance, LPCTSTR szTitle) override;
    virtual void UnInitialize();
    // WinGameApp을(를) 통해 상속됨
    void Update(float deltatime) override;
    void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
};

