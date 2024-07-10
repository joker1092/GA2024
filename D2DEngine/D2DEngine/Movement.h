#pragma once
#include "Component.h"
#include "MathHelper.h"

class Scene;
class Movement :public Component
{
public:
	Movement() = default;
	virtual ~Movement() = default;
protected:
	float m_fSpeed = 0.0f;
	MathHelper::Vector2F m_vDirection = { 0.0f,0.0f };
	MathHelper::Vector2F m_vVelocity;
	Scene* m_pScene; //위치정보를 가진 Scene;
public:
	virtual void Update(float deltaTime);

	void SetScene(Scene* pScene) { m_pScene = pScene; }
	void SetSpeed(float speed) { m_fSpeed = speed; }
	virtual void SetDirection(MathHelper::Vector2F direction);
	float GetSpeed() { return m_fSpeed; }
	MathHelper::Vector2F GetDirection() { return m_vDirection; }
};

