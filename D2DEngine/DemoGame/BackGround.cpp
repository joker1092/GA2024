#include "../D2DEngine/AnimationScene.h"
#include "../D2DEngine/BitmapScene.h"
#include "BackGround.h"

BackGround::BackGround()
{
	m_ZOrder = ZOrder::BACKGROUND; 
	pBitmapScene = CreateComponent<BitmapScene>();
	SetRootScene(pBitmapScene);
	pBitmapScene->LoadD2DBitmap(L"../Resource/camerabackgound.png");
	/*pAnimationScene->LoadAnimationAsset(L"Background");
	pAnimationScene->SetAnimation(0, false);*/
	pBitmapScene->m_RelativeScale = { 3.8, 4.8 };
	pBitmapScene->m_RelativeLocation = { 0, 1000 };
}

void BackGround::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	//m_BoundBox.m_Center.x = m_pRootScene->GetWorldLocation().x + pBitmapScene->pBitmap->GetSize().width / 2;
	//m_BoundBox.m_Center.y = m_pRootScene->GetWorldLocation().y + pBitmapScene->pBitmap->GetSize().height / 2;
}
