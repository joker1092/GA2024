#pragma once
#include "../D2DEngine/Scene.h"

//���� ���Ÿ� ������ �����ϴ� Ŭ����

class EnemyBulletScene : public Scene
{
	//bullet�� ������ ����
	World* m_pWorld = nullptr;
	Player* m_pPlayer = nullptr;

	public:
	MathHelper::Vector2F dir;
	EnemyBulletScene();
	virtual ~EnemyBulletScene();

	//���� ���Ÿ� ������ �����ϴ� �Լ�
	void CreateBullet(MathHelper::Vector2F dir);
	//���� ���⿡ ���� �߻� ��ġ�� �����ϴ� �Լ�
	virtual void Update(float deltaTime);
};

