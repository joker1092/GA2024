#pragma once
#include "../D2DEngine/GameObject.h"
class MapBackgound : public GameObject
{
	BitmapScene* pBitmapScene;
public:
	MapBackgound();
	virtual ~MapBackgound() = default;
	virtual void Update(float deltaTime);
};

