#include "DemoGameApp.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<long> uniform_dist(100, 600); // 0부터 99까지 균등 분포
std::uniform_int_distribution<int> miror(0, 1); // 0부터 99까지 균등 분포

void DemoGameApp::Initialize(HINSTANCE hInstance, LPCTSTR szTitle)
{
	WinGameApp::Initialize(hInstance, szTitle);
	//todo
	
	
	RECT rc;
	GetClientRect(m_hWnd, &rc);
	//bg.SetDstRect(D2D1::RectF(rc.left, rc.top, rc.right, rc.bottom));
	backGound = m_pWorld->CreateGameObject<GameObject>();
	animeSceneBG = backGound->CreateComponent<AnimationScene>();
	backGound->SetRootScene(animeSceneBG);
	backGound->m_ZOrder = GameObject::ZOrder::BACKGROUND;
	animeSceneBG->LoadD2DBitmap(L"../Resource/midnight.png", pD2DRender);
	animeSceneBG->LoadAnimationAsset(L"Background");
	player = m_pWorld->CreateGameObject<GameObject>();
	animeScenePlayer = player->CreateComponent<AnimationScene>();
	player->SetRootScene(animeScenePlayer);
	backGound->m_ZOrder = GameObject::ZOrder::PLAYER;
	animeScenePlayer->LoadD2DBitmap(L"../Resource/run.png", pD2DRender);
	animeScenePlayer->LoadAnimationAsset(L"Run");
	animeScenePlayer->SetAnimaitonIndex(1);
	animeScenePlayer->SetMiror(false);
	animeScenePlayer->SetLocation({ 800, 400 });
}

void DemoGameApp::UnInitialize()
{
	
	//todo
	/*Sun.~BitmapScene();
	Earth.~BitmapScene();
	Moon.~BitmapScene();*/
	
	backGound->~GameObject();
	player->~GameObject();
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
	std::cout <<"delta : " << deltatime << ""<< std::endl;
	//std::cout << player.curFrameIndex << std::endl;
	//std::cout <<"elepse :"<< elepsedTime << std::endl;*/
	//todo

	
	/*position.x++;
	if (position.x > 1240) {
		position.x = 0;
	}*/
	//player.SetLocation(position);

	//방향에 따른 카메라 이동
	if (pInput->IsKey(VK_LEFT))
	{
		m_pWorld->GetCamera()->vRelativeLcation.x -= 1;
	}
	if (pInput->IsKey(VK_RIGHT))
	{
		m_pWorld->GetCamera()->vRelativeLcation.x += 1;
	}
	if (pInput->IsKey(VK_UP))
	{
		m_pWorld->GetCamera()->vRelativeLcation.y -= 1;
	}
	if (pInput->IsKey(VK_DOWN))
	{
		m_pWorld->GetCamera()->vRelativeLcation.y += 1;
	}

	


	if (pInput->IsKey('A'))
	{
		GameObject* cObjPlayer = m_pWorld->CreateGameObject<GameObject>();
		AnimationScene* cPlayer = cObjPlayer->CreateComponent<AnimationScene>();
		cObjPlayer->SetRootScene(cPlayer);
		cPlayer->LoadD2DBitmap(L"../Resource/run.png", pD2DRender);
		cPlayer->LoadAnimationAsset(L"Run");
		cPlayer->SetAnimaitonIndex(1);
		cPlayer->SetMiror(miror(gen));
		backGound->m_ZOrder = GameObject::ZOrder::ENEMY;
		float x=uniform_dist(gen);
		float y = uniform_dist(gen);
		cPlayer->SetLocation({ (float)x,(float)y });
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
			float x = animeScnene->vRelativeLcation.x;
			
			if (animeScnene->bMiror)
			{
				//std::cout << "x" << x << std::endl;
				--x;
				if (x < 200)
				{
					x = 1200;
				}
				
			}
			else {
				x++;
				if (x > 1200)
				{
					x = 200;
				}
			}
			
			animeScnene->SetLocation({ x,animeScnene->vRelativeLcation.y });
			animeScnene->Update(deltatime);
		}
	}
	WinGameApp::Update(deltatime);
}

void DemoGameApp::Render(ID2D1RenderTarget* pRenderTarget)
{
	WinGameApp::Render(pRenderTarget);
}
