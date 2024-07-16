#pragma once
#include "../D2DEngine/GameObject.h"

class BitmapScene;
class BoxCollider;
class BoxObject : public GameObject
{
	BitmapScene* m_pBitmapScene = nullptr;
	BoxCollider* m_pBoxCollider = nullptr;
	public:
	BoxObject();
	virtual ~BoxObject() = default;
	virtual void Update(float deltaTime);
};

