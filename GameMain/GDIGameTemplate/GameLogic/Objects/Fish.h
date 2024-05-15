#pragma once
#include "Object.h"

class Fish : public Object {
private:
	float m_speed = 50.f;
	float time = 0.f;
	float maxTime = 0.f;
	Vector2 m_moveDirection;

	void Move(float delta);
	Vector2 GetRandomPosition();

	// regacy
	float m_AngulerSpeed = 8.f;
	// regacy
	Vector2 m_AngulerDirection;
	// regacy
	void AngularVelocity(float delta);
	// regacy
	Vector2 GetRandomDirection();
	//Bounds renderBounds2;

	Gdiplus::Bitmap* m_FishImage;

	const static int x1 = 100;
	const static int y1 = 100;
	const static int x2 = 800;
	const static int y2 = 620;

public:
	void Init() override;
	void Update(float delta) override;
	void Render() override;
	void OnTrigger() override;
};