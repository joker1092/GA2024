#include "../D2DEngine/AnimationScene.h"
#include "../D2DEngine/BitmapScene.h"
#include "MapBackgound.h"

MapBackgound::MapBackgound()
{
	float width = 1920;
	float height = 1280;
	m_ZOrder = ZOrder::MAP;
	pBitmapScene = CreateComponent<BitmapScene>();
	SetRootScene(pBitmapScene);
	pBitmapScene->LoadD2DBitmap(L"../Resource/mapbackground.png");
	/*pAnimationScene->LoadAnimationAsset(L"Background");
	pAnimationScene->SetAnimation(0, false);*/
	pBitmapScene->m_RelativeScale = {4.5, 4.5 };
	pBitmapScene->m_RelativeLocation = {-600 ,700 };
	
}

void MapBackgound::Update(float deltaTime)
{
	//std::cout << m_pRootScene->GetWorldLocation().x << "," << m_pRootScene->GetWorldLocation().y << std::endl;
	GameObject::Update(deltaTime);

	//m_BoundBox.m_Center.x = m_pRootScene->GetWorldLocation().x + pBitmapScene->pBitmap->GetSize().width / 2;
	//m_BoundBox.m_Center.y = m_pRootScene->GetWorldLocation().y + pBitmapScene->pBitmap->GetSize().height / 2;
}
