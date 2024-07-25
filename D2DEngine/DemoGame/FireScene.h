#pragma once
#include "../D2DEngine/Scene.h"

//Player의 원거리 공격을 생성하는 클래스

class FireScene : public Scene
{
	World* m_pWorld = nullptr;

	public:
	FireScene();
	virtual ~FireScene() = default;
	//Player의 원거리 공격을 생성하는 함수
	void CreateFire( MathHelper::Vector2F dir);
	//player의 방향에 따라 발사 위치를 조정하는 함수
	virtual void Update(float deltaTime);
	
};

