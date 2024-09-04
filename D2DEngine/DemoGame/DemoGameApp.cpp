#include "DemoGameApp.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<long> uniform_dist(0, 1200); // 0부터 99까지 균등 분포
std::uniform_int_distribution<int> miror(0, 1); // 0부터 99까지 균등 분포

class FSMState;
class GameObject;
class Bullet;
class EnemyBullet;
class FireScene;

void DemoGameApp::Initialize(HINSTANCE hInstance, LPCTSTR szTitle)
{
	WinGameApp::Initialize(hInstance, szTitle);
	//todo
	
	
	RECT rc;
	GetClientRect(m_hWnd, &rc);
	backGound = m_pWorld->CreateGameObject<BackGround>();
	m_pCamera = m_pWorld->GetCamera();
	player = m_pWorld->CreateGameObject<Player>();	
	player->PlayerInit(pInput);

	m_pCamera->SetTargetScene(player->m_pRootScene);
	
	for (size_t i = 0; i < rifleCount; i++)
	{
		EnemyRifle* enemyRifle = m_pWorld->CreateGameObject<EnemyRifle>();
		vObjList.push_back(enemyRifle);
	}

	for (size_t i=0; i < 5; i++)
	{
		float x = 1200 + (100 * i);
		vObjList[i]->m_pRootScene->SetRelativeLocation({x,100 });
	}
	
	for (size_t i = 5; i < 10; i++)
	{
		float x = 1200 + (100 * i);
		vObjList[i]->m_pRootScene->SetRelativeLocation({ x,500 });
	}
	
	
	for (size_t i = 0; i < 40; i++)
	{
		boxObject = m_pWorld->CreateGameObject<BoxObject>();
		float x = (80 * i);
		boxObject->m_pRootScene->SetRelativeLocation({ x,50});
	}
	
	for (size_t i = 0; i < 10; i++)
	{
		boxObject = m_pWorld->CreateGameObject<BoxObject>();
		float x = 500+(80 * i);
		boxObject->m_pRootScene->SetRelativeLocation({ x,250 });
	}

	for (size_t i = 0; i < 10; i++)
	{
		boxObject = m_pWorld->CreateGameObject<BoxObject>();
		float x = 1400 + (80 * i);
		boxObject->m_pRootScene->SetRelativeLocation({ x,450 });
	}
}

void DemoGameApp::UnInitialize()
{
	

	backGound->~BackGround();
	//mapBackGound->~MapBackgound();
	player->~Player();
	//player.~AnimationScene();
	//player2.~AnimationScene();
	/*for (auto& objScene : vObjList)
	{
		objScene->~AnimationScene();
	}*/
	WinGameApp::UnInitialize();
}

void DemoGameApp::Update(float deltatime)
{
	m_pWorld->GetCamera()->ObjectClampToCamera(player->m_pRootScene);
	if (player->GetWorldLocation().x > 1400)
	{
		m_pWorld->GetCamera()->SetFixedLocation({ 400,0 });
	}

	for (auto rifle : vObjList)
	{
		if (rifle->isDead)
		{
			rifleCount--;
			vObjList.erase(std::remove(vObjList.begin(), vObjList.end(), rifle), vObjList.end());
		}
	}

	if (rifleCount==0)
	{
		m_pWorld->GetCamera()->ReleaseFixedLocation();
	}


	WinGameApp::Update(deltatime);
}

void DemoGameApp::Render(ID2D1RenderTarget* pRenderTarget)
{
	WinGameApp::Render(pRenderTarget);
}
