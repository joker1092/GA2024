#pragma once
#include "CScene.h"
class IntroScene : public CScene
{
private:

public:
    // CScene��(��) ���� ��ӵ�
    void Init() override;
    void Start() override;
   
    void Exit() override;

    IntroScene();
    ~IntroScene();
};

