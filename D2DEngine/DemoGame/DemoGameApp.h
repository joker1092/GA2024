#pragma once
#include "../D2DEngine/WinGameApp.h"
#include "../D2DEngine/BitmapScene.h"
class DemoGameApp :public WinGameApp
{
    BitmapScene Sun;
    BitmapScene Earth;
    BitmapScene Moon;
public:
    float rotate = 0;
    virtual void Initialize(HINSTANCE hInstance, LPCTSTR szTitle) override;
    virtual void UnInitialize();
    // WinGameApp��(��) ���� ��ӵ�
    void Update() override;
    void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
};

