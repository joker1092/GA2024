#include "framework.h"
#include "../D2DEngine/World.h"
#include "../D2DEngine/MathHelper.h"
#include "FireScene.h"
#include "Bullet.h"
#include "Player.h"
FireScene::FireScene()
{
}

void FireScene::CreateFire(MathHelper::Vector2F dir)
{
	Bullet* bullet = m_pWorld->CreateGameObject<Bullet>();
	bullet->m_ZOrder = GameObject::ZOrder::EFFECT;
	bullet->SetDirection(dir);
	bullet->m_pRootScene->SetRelativeLocation(GetWorldLocation());
}

void FireScene::Update(float deltaTime)
{
	//player의 방향과 입력에 따라 발사 위치를 조정

	Player* player = dynamic_cast<Player*>(m_pOwner);
	if (player->flip)
	{
		m_RelativeLocation.x =-30;
	}
	else {
		m_RelativeLocation.x = 30;
	}
	Scene::Update(deltaTime);
}


