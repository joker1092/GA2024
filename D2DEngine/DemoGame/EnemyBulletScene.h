#pragma once
#include "../D2DEngine/Scene.h"

//적의 원거리 공격을 생성하는 클래스

class EnemyBulletScene : public Scene
{
	//bullet을 생성할 월드
	World* m_pWorld = nullptr;
	Player* m_pPlayer = nullptr;

	public:
	MathHelper::Vector2F dir;
	EnemyBulletScene();
	virtual ~EnemyBulletScene();

	//적의 원거리 공격을 생성하는 함수
	void CreateBullet(MathHelper::Vector2F dir);
	//적의 방향에 따라 발사 위치를 조정하는 함수
	virtual void Update(float deltaTime);
};

