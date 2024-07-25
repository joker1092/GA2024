#pragma once
#include "../D2DEngine/Scene.h"

//Player�� ���Ÿ� ������ �����ϴ� Ŭ����

class FireScene : public Scene
{
	World* m_pWorld = nullptr;

	public:
	FireScene();
	virtual ~FireScene() = default;
	//Player�� ���Ÿ� ������ �����ϴ� �Լ�
	void CreateFire( MathHelper::Vector2F dir);
	//player�� ���⿡ ���� �߻� ��ġ�� �����ϴ� �Լ�
	virtual void Update(float deltaTime);
	
};

