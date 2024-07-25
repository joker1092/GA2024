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
	Enemybullet* bullet = m_pWorld->CreateGameObject<Enemybullet>(); // todo : enemy bullet ���� ����
	bullet->m_ZOrder = GameObject::ZOrder::EFFECT;
	bullet->SetDirection(dir);
	MathHelper::Vector2F pos = m_pParentScene->GetWorldLocation();
	
	bullet->m_pRootScene->SetRelativeLocation(pos);
}

void EnemyBulletScene::Update(float deltaTime)
{
	//���� ����� �Է¿� ���� �߻� ��ġ�� ����
	EnemyRifle* enemy = dynamic_cast<EnemyRifle*>(m_pOwner); //todo :  EnemyRifle ===> Enemy�� ���� ���� ������ Ŭ������ ���� ����
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
