#pragma once
#include "framework.h"
#include "Scene.h"
#include "AABB.h"
#include "Component.h"

// 카메라 클래스
class World;
class Camera:public Scene
{
public:
	Camera();
	virtual ~Camera();

	World* pWorld = nullptr; // 카메라가 속한 월드
	AABB m_ViewBoundBox;
	
	virtual void Update(float deltaTime);
	//camera tracking
	Scene* pTargetScene = nullptr;
	void SetTargetScene(Scene* _pTargetScene) { pTargetScene=_pTargetScene; }
	void SetWorld(World* _pWorld) { pWorld = _pWorld; }
};

