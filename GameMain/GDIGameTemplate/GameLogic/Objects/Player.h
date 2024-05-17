#pragma once
#include "Object.h"
class Event;

class Player : public Object
{
private:
	float moveSpeed;
	float radius;
	Vector2 moveDirection;
	float up = -1;
	float down = 1;
	float left = -1;
	float right = 1;

	Gdiplus::Bitmap* playerBitmap;

	bool isScoopUp = false;
	float scoopUpTime = 0.f;
	float scale = 1.f;
	bool isOnScoopUpSound;

	bool isAwake;
public:
	Event* pauseEvent;
	Player();
	~Player() override { delete playerBitmap; }

	void Init() override;
	void Update(float delta) override;
	void Render(float alpha) override;
	void OnTrigger() override;

	void movePlayer(float delta);
	void ScoopUp(float delta);
};

