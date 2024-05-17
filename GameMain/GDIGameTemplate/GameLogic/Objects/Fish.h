#pragma once
#include "Object.h"

class Fish : public Object {
private:
	float m_speed = 50.f;
	float time = 0.f;
	float maxTime = 0.f;
	float m_AngulerSpeed = 8.f;
	Vector2 m_moveDirection;
	Vector2 m_AngulerDirection;
	float m_rotateInterval1;
	float m_rotateInterval2;

	float animTime = 0.f;
	float animMaxTime = 0.03f;
	int animationFrame = 0;

	float alphaTime = 1.f;
	bool isCatch = false;

	void Move(float delta);
	void AngularVelocity(float delta);
	Vector2 GetRandomPosition();
	Vector2 GetRandomDirection();
	//Bounds renderBounds2;

	const static int x1 = 100;
	const static int y1 = 100;
	const static int x2 = 800;
	const static int y2 = 620;

	std::wstring m_fileName[30];
	Gdiplus::Bitmap* m_bitmap[30] = { nullptr, };

public:
	Fish(const WCHAR* name, float moveSpeed, float angulerSpeed, const WCHAR* fileName, CResourceManager* CRM, const WCHAR* imageType, float rotateInterval1, float rotateInterval2, float colliderWidth, float colliderHeight);
	void Init() override;
	void Update(float delta) override;
	void Render(float alpha) override;
	void OnTrigger() override;

	void SetRandomPosition();
	void LoadAnimImage(const WCHAR* fileName, CResourceManager* CRM, const WCHAR* imageType);
};