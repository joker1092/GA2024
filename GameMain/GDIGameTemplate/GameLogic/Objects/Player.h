#pragma once
#include "Object.h"
class Event;

class Player : public Object
{
private:
	float moveSpeed;
	float radius;
	Vector2 moveDirection;
	bool flag;

	Gdiplus::Bitmap* playerBitmap;
public:
	Event* pauseEvent;
	Player();
	~Player();

	void Init() override;
	void Update(float delta) override;
	void Render() override;
	void OnTrigger() override;

	void movePlayer(float delta);

	void Up(float delta);
	void Down(float delta);
	void Left(float delta);
	void Right(float delta);

	void SetStatus();
};

