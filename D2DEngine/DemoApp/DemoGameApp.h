#pragma once
#include "../D2DEngine/WinGameApp.h"
class DemoGameApp :
    public WinGameApp
{
    // WinGameApp을(를) 통해 상속됨
    virtual bool Intialize(HINSTANCE hInstance, LPCTSTR appName) override;
    void Update() override;
    void Render() override;
};


