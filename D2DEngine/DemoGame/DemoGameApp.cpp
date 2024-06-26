#include "DemoGameApp.h"

void DemoGameApp::Initialize(HINSTANCE hInstance, LPCTSTR szTitle)
{
	WinGameApp::Initialize(hInstance, szTitle);
	//todo
	bg.LoadD2DBitmap(L"../Resource/midnight.png", pD2DRender);
	bg.LoadAnimationAsset(L"Background");
	RECT rc;
	GetClientRect(m_hWnd, &rc);
	//bg.SetDstRect(D2D1::RectF(rc.left, rc.top, rc.right, rc.bottom));
	bg.SetLocation({604	,246 });
	bg.SetScale({ 3.28,3.06 });
	//vObjList.push_back(&bg);
	/*player.LoadD2DBitmap(L"../Resource/run.png", pD2DRender);
	player.LoadAnimationAsset(L"Run");
	player.SetAnimaitonIndex(1);
	position = { 200,300 };
	player.SetLocation(position);*/
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
	//player.~AnimationScene();

	for (auto& objScene : vObjList)
	{
		objScene->~AnimationScene();
	}
	WinGameApp::UnInitialize();
}

void DemoGameApp::Update(float deltatime)
{
	/*std::cout <<"delta : " << deltatime << "";
	std::cout <<"elepse :"<< elepsedTime << std::endl;*/
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
		cPlayer->SetLocation({ 200,100 });
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
	//player.Update(deltatime);
	if (!vObjList.empty()) {
		for (auto& objScene : vObjList)
		{
			float x = objScene->vRelativeLcation.x;
			x++;
			if (x > 1240)
			{
				x = 200;
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
	
	//player.Render(pRenderTarget);

	/*Sun.Render(pRenderTarget);
	Earth.Render(pRenderTarget);
	Moon.Render(pRenderTarget);*/
}
