#include "framework.h"
#include "../D2DEngine/World.h"
#include "../D2DEngine/MathHelper.h"
#include "../D2DEngine/GameObject.h"
#include "Player.h"
#include "Enemybullet.h"
#include "EnemyRifle.h"
#include "EnemyBulletScene.h"

EnemyBulletScene::EnemyBulletScene()
{
	m_RelativeLocation.x = 30;
}

EnemyBulletScene::~EnemyBulletScene()
{
}

void EnemyBulletScene::CreateBullet(MathHelper::Vector2F dir)
{
	m_pWorld = m_pOwner->m_pOwner;
	m_pPlayer = m_pWorld->FindPointGameObject<Player>();
	Enemybullet* bullet = m_pWorld->CreateGameObject<Enemybullet>(); // todo : enemy bullet 으로 변경
	bullet->m_ZOrder = GameObject::ZOrder::EFFECT;
	bullet->SetDirection(dir);
	MathHelper::Vector2F pos = m_pParentScene->GetWorldLocation();
	
	bullet->m_pRootScene->SetRelativeLocation(pos);
}

void EnemyBulletScene::Update(float deltaTime)
{
	//적의 방향과 입력에 따라 발사 위치를 조정
	EnemyRifle* enemy = dynamic_cast<EnemyRifle*>(m_pOwner); //todo :  EnemyRifle ===> Enemy로 변경 상위 개념의 클래스로 변경 예정
	m_pWorld = enemy->m_pOwner;
	m_pPlayer = m_pWorld->FindPointGameObject<Player>();
	MathHelper::Vector2F PlayerLocation = m_pPlayer->GetWorldLocation();
	MathHelper::Vector2F EnemyLocation = enemy->GetWorldLocation();
	dir = PlayerLocation - EnemyLocation;
	dir.Normalize();
	MathHelper::Vector2F pos =  dir * 30;
	m_RelativeLocation = pos;
	
	Scene::Update(deltaTime);
}
