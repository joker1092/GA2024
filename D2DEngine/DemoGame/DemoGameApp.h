#pragma once
#include "../D2DEngine/WinGameApp.h"
class DemoGameApp :public WinGameApp
{
public:
    virtual bool Initialize(HINSTANCE hInstance, LPCTSTR szTitle) override;
    virtual void UnInitialize();
    // WinGameApp��(��) ���� ��ӵ�
    void Update() override;
    void Render() override;
};

