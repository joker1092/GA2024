#pragma once
#include "Object.h"

class Fish : public Object {
private:
	float m_speed = 50.f;
	float time = 0.f;
	float maxTime = 0.f;
	Vector2 m_moveDirection;

	float animTime = 0.f;
	float animMaxTime = 0.f;
	int animationFrame = 0;

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

	std::wstring m_fileName[30];
	Gdiplus::Bitmap* m_bitmap[30] = { nullptr, };

public:
	void Init() override;
	void Update(float delta) override;
	void Render(float alpha) override;
	void OnTrigger() override;

	void SetRandomPosition();
	void LoadAnimImage(const WCHAR* fileName, CResourceManager* CRM);
};