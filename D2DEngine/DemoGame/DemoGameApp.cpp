#include "DemoGameApp.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<long> uniform_dist(0, 1200); // 0부터 99까지 균등 분포
std::uniform_int_distribution<int> miror(0, 1); // 0부터 99까지 균등 분포

class FSMState;
void DemoGameApp::Initialize(HINSTANCE hInstance, LPCTSTR szTitle)
{
	WinGameApp::Initialize(hInstance, szTitle);
	//todo
	
	
	RECT rc;
	GetClientRect(m_hWnd, &rc);
	//bg.SetDstRect(D2D1::RectF(rc.left, rc.top, rc.right, rc.bottom));
	backGound = m_pWorld->CreateGameObject<BackGround>();
	m_pCamera = m_pWorld->GetCamera();
	mapBackGound = m_pWorld->CreateGameObject<MapBackgound>();
	/*animeSceneBG = backGound->CreateComponent<AnimationScene>();
	backGound->SetRootScene(animeSceneBG);
	backGound->m_ZOrder = GameObject::ZOrder::BACKGROUND;*/
	/*animeSceneBG->LoadD2DBitmap(L"../Resource/midnight.png");
	animeSceneBG->LoadAnimationAsset(L"Background");
	animeSceneBG->SetAnimation(0, false);*/
	player = m_pWorld->CreateGameObject<Player>();	
	player->PlayerInit(pInput);
	enemyRifle = m_pWorld->CreateGameObject<EnemyRifle>();
	m_pCamera->SetTargetScene(player->m_pRootScene);

	boxObject = m_pWorld->CreateGameObject<BoxObject>();
	boxObject->m_pRootScene->SetRelativeLocation({ 400,0 });
}

void DemoGameApp::UnInitialize()
{
	
	//todo
	/*Sun.~BitmapScene();
	Earth.~BitmapScene();
	Moon.~BitmapScene();*/
	
	backGound->~BackGround();
	mapBackGound->~MapBackgound();
	player->~Player();
	enemyRifle->~EnemyRifle();
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
	//std::cout <<"delta : " << deltatime << ""<< std::endl;
	//std::cout << player.curFrameIndex << std::endl;
	//std::cout <<"elepse :"<< elepsedTime << std::endl;*/
	//todo

	
	/*position.x++;
	if (position.x > 1240) {
		position.x = 0;
	}*/
	//player.SetLocation(position);
	//pPlayerMovement->SetDirection({ 0,0 });

	//방향에 따른 카메라 이동
	// 
	//player->Update(deltatime);
	//if (pInput->IsKey(VK_LEFT))
	//{
	//	pPlayerMovement->SetDirection({ -1,0 });
	//	//m_pWorld->GetCamera()->m_RelativeLocation.x -= 1;
	//}
	//if (pInput->IsKey(VK_RIGHT))
	//{
	//	pPlayerMovement->SetDirection({ 1,0 });
	//	//m_pWorld->GetCamera()->m_RelativeLocation.x += 1;
	//}
	//if (pInput->IsKey(VK_UP))
	//{
	//	pPlayerMovement->SetDirection({ 0,1 });
	//	//m_pWorld->GetCamera()->m_RelativeLocation.y += 1;
	//}
	//if (pInput->IsKey(VK_DOWN))
	//{
	//	pPlayerMovement->SetDirection({ 0,-1 });
	//	//m_pWorld->GetCamera()->m_RelativeLocation.y -= 1;
	//}

	


	if (pInput->IsKey('A'))
	{
		GameObject* cObjPlayer = m_pWorld->CreateGameObject<GameObject>();
		cObjPlayer->m_ZOrder = GameObject::ZOrder::ENEMY;
		AnimationScene* cPlayer = cObjPlayer->CreateComponent<AnimationScene>();
		cObjPlayer->SetRootScene(cPlayer);
		cPlayer->LoadD2DBitmap(L"../Resource/run.png");
		cPlayer->LoadAnimationAsset(L"Run");
		cPlayer->SetAnimation(1, miror(gen));
		backGound->m_ZOrder = GameObject::ZOrder::ENEMY;
		float x=uniform_dist(gen);
		float y = uniform_dist(gen);
		cPlayer->m_RelativeLocation.x = x;
		cPlayer->m_RelativeLocation.y = y;
		
		vObjList.push_back(cObjPlayer);
		//todo : obj add
	}

	if (pInput->IsKey('D'))
	{
		if (vObjList.size() >0)
		{
			GameObject* a = vObjList.back();
			if (m_pWorld->DeleteGameObject(a))
			{
				vObjList.erase(vObjList.end() - 1);
			}
		}
		//todo : obj delete
	}

	////bg.Update(deltatime);
	////player.Update(deltatime);
	//
	////player2.Update(deltatime);
	if (!vObjList.empty()) {
		for (auto& objScene : vObjList)
		{
			AnimationScene* animeScnene = dynamic_cast<AnimationScene*>(objScene->m_pRootScene);
			float x = animeScnene->m_RelativeLocation.x;
			
			//if (animeScnene->m_bMirror)
			//{
			//	//std::cout << "x" << x << std::endl;
			//	--x;
			//	if (x < 200)
			//	{
			//		x = 1200;
			//	}
			//	
			//}
			//else {
			//	x++;
			//	if (x > 1200)
			//	{
			//		x = 200;
			//	}
			//}
			
			animeScnene->m_RelativeLocation.x = x;
			animeScnene->Update(deltatime);
		}
	}
	
	WinGameApp::Update(deltatime);
}

void DemoGameApp::Render(ID2D1RenderTarget* pRenderTarget)
{
	WinGameApp::Render(pRenderTarget);
}
