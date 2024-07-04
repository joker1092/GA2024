#pragma once
#include "framework.h"
#include "Scene.h"
#include "AABB.h"
#include "Component.h"

// 카메라 클래스
class Camera:public Scene
{
public:
	Camera();
	virtual ~Camera();

	AABB m_ViewBoundBox;
	
	virtual void Update(float deltaTime);
	
};

