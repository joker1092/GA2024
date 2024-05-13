#pragma once
#include "Object.h"

class Fish : public Object {
private:
	float m_speed = 50.f;
	float m_AngulerSpeed = 500.f;
	float time = 0.f;
	float maxTime = 5.f;
	Vector2 m_moveDirection;
	Vector2 m_AngulerDirection;
	void Move(float delta);
	void AngularVelocity(float delta);
	Vector2 GetRandomDirection();

public:
	void Init() override;
	void Update(float delta) override;
	void Render() override;
	void OnTrigger() override;
};