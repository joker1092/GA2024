#pragma once
#include "framework.h"
#include "Scene.h"
#include "AABB.h"
#include "Component.h"

class Camera:public Scene, public Component
{
public:
	Camera();
	virtual ~Camera();

	AABB m_ViewBoundBox;

	virtual void Update(float deltaTime);
};

