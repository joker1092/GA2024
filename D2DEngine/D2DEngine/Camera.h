#pragma once
#include "framework.h"
#include "Scene.h"
#include "AABB.h"
#include "Component.h"

// ī�޶� Ŭ����
class Camera:public Scene
{
public:
	Camera();
	virtual ~Camera();

	AABB m_ViewBoundBox;
	
	virtual void Update(float deltaTime);
	
};

