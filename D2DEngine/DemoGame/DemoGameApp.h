#pragma once
#include "../D2DEngine/WinGameApp.h"
#include "../D2DEngine/Scene.h"
#include "../D2DEngine/BitmapScene.h"
#include "../D2DEngine/AnimationScene.h"
#include "../D2DEngine/Camera.h"
#include "../D2DEngine/FSM.h"
#include "../D2DEngine/FSMState.h"
#include "../D2DEngine/Movement.h"
#include "BackGround.h"
#include "MapBackgound.h"
#include "Player.h"
#include "EnemyRifle.h"
#include "BoxObject.h"
#include "Bullet.h"
#include "Enemybullet.h"
#include "FireScene.h"

#include <random>
class DemoGameApp :public WinGameApp
{
    BackGround* backGound;
    MapBackgound* mapBackGound;
    Player* player;
    AnimationScene* animeSceneBG;
    EnemyRifle* enemyRifle;
    BoxObject* boxObject;
    
    std::vector<GameObject*> vObjList;

public:
    D2D1_VECTOR_2F position;
    //float rotate = 0;
    virtual void Initialize(HINSTANCE hInstance, LPCTSTR szTitle) override;
    virtual void UnInitialize();
    // WinGameApp을(를) 통해 상속됨
    void Update(float deltatime) override;
    void Render(ID2D1RenderTarget* pRenderTarget) override;
};

