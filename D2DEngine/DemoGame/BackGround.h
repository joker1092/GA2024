#pragma once
#include "../D2DEngine/GameObject.h"
class BackGround : public GameObject
{
	BitmapScene* pBitmapScene;
	public:
	BackGround();
	virtual ~BackGround() = default;
	virtual void Update(float deltaTime);
};

