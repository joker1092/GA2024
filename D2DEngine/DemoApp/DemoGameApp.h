#pragma once
#include "../D2DEngine/WinGameApp.h"
class DemoGameApp :
    public WinGameApp
{
    // WinGameApp��(��) ���� ��ӵ�
    virtual bool Intialize(HINSTANCE hInstance, LPCTSTR appName) override;
    void Update() override;
    void Render() override;
};


