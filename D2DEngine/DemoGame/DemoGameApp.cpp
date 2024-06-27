#include "DemoGameApp.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<long> uniform_dist(100, 600); // 0부터 99까지 균등 분포
std::uniform_int_distribution<int> miror(0, 1); // 0부터 99까지 균등 분포

void DemoGameApp::Initialize(HINSTANCE hInstance, LPCTSTR szTitle)
{
	WinGameApp::Initialize(hInstance, szTitle);
	//todo
	
	bg.LoadD2DBitmap(L"../Resource/midnight.png", pD2DRender);
	bg.LoadAnimationAsset(L"Background");
	RECT rc;
	GetClientRect(m_hWnd, &rc);
	//bg.SetDstRect(D2D1::RectF(rc.left, rc.top, rc.right, rc.bottom));
	bg.SetLocation({ 0,0 });
	bg.SetScale({1,1});
	//vObjList.push_back(&bg);
	player.LoadD2DBitmap(L"../Resource/run.png", pD2DRender);
	player.LoadAnimationAsset(L"Run");
	player.SetAnimaitonIndex(1);
	player.SetMiror(false);
	player.SetLocation({ 800, 400 });

	/*player2.LoadD2DBitmap(L"../Resource/run.png", pD2DRender);
	player2.LoadAnimationAsset(L"Run");
	player2.SetAnimaitonIndex(1);
	player2.SetMiror(true);
	player2.SetLocation({ 800, 500 });*/
	//vObjList.push_back(&player);
	
	/*Sun.LoadD2DBitmap(L"../Resource/sun.jpg", pD2DRender);
	Earth.LoadD2DBitmap(L"../Resource/earth.jpg", pD2DRender);
	Moon.LoadD2DBitmap(L"../Resource/moon.jpg", pD2DRender);
	Sun.SetLocation({ 640,480 });
	Sun.SetScale({1.5,1.5});
	Earth.SetParant(&Sun);
	Earth.SetScale({ 0.5,0.5 });
	Earth.SetLocation({ 200,200 });
	Moon.SetParant(&Earth);
	Moon.SetScale({ 0.5,0.5 });
	Moon.SetLocation({ 200,200 });*/

}
void DemoGameApp::UnInitialize()
{
	//todo
	/*Sun.~BitmapScene();
	Earth.~BitmapScene();
	Moon.~BitmapScene();*/
	bg.~AnimationScene();
	player.~AnimationScene();
	//player2.~AnimationScene();
	for (auto& objScene : vObjList)
	{
		objScene->~AnimationScene();
	}
	WinGameApp::UnInitialize();
}

void DemoGameApp::Update(float deltatime)
{
	std::cout <<"delta : " << deltatime << ""<< std::endl;
	std::cout << player.curFrameIndex << std::endl;
	//std::cout <<"elepse :"<< elepsedTime << std::endl;*/
	//todo

	
	/*position.x++;
	if (position.x > 1240) {
		position.x = 0;
	}*/
	//player.SetLocation(position);
	if (pInput->IsKey('A'))
	{
		AnimationScene* cPlayer = new AnimationScene;
		cPlayer->LoadD2DBitmap(L"../Resource/run.png", pD2DRender);
		cPlayer->LoadAnimationAsset(L"Run");
		cPlayer->SetAnimaitonIndex(1);
		cPlayer->SetMiror(miror(gen));
		
		float x=uniform_dist(gen);
		float y = uniform_dist(gen);
		cPlayer->SetLocation({ (float)x,(float)y });
		vObjList.push_back(cPlayer);
		//todo : obj add
	}

	if (pInput->IsKey('D'))
	{
		std::cout << "size : " << vObjList.size() << std::endl;
		if (vObjList.size() >0)
		{
			AnimationScene* a = vObjList.back();
			vObjList.erase(vObjList.end() - 1);
			a->~AnimationScene();
		}
		//todo : obj delete
	}

	bg.Update(deltatime);
	player.Update(deltatime);
	
	//player2.Update(deltatime);
	if (!vObjList.empty()) {
		for (auto& objScene : vObjList)
		{
			float x = objScene->vRelativeLcation.x;
			if (objScene->bMiror)
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
			
			objScene->SetLocation({ x,objScene->vRelativeLcation.y });
			objScene->Update(deltatime);
		}
	}

	/*Sun.SetRotation(rotate);
	Sun.Update();
	Earth.SetRotation(rotate);
	Earth.Update();
	Moon.SetRotation(rotate);
	Moon.Update();
	rotate++;
	Sun.Update();
	Earth.Update();
	Moon.Update();*/
}

void DemoGameApp::Render(ID2D1HwndRenderTarget* pRenderTarget)
{

	//todo
	bg.Render(pRenderTarget);
	if (!vObjList.empty())
	{
		for (auto& objScene : vObjList)
		{
			objScene->Render(pRenderTarget);
		}
	}
	
	player.Render(pRenderTarget);
	//player2.Render(pRenderTarget);

	/*Sun.Render(pRenderTarget);
	Earth.Render(pRenderTarget);
	Moon.Render(pRenderTarget);*/
}
