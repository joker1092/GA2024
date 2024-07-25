#pragma once
#include "framework.h"
#include "Scene.h"
#include "AABB.h"
#include "Component.h"

// ī�޶� Ŭ����
class World;
class Camera:public Scene
{
public:
	Camera();
	virtual ~Camera();

	World* pWorld = nullptr; // ī�޶� ���� ����
	AABB m_ViewBoundBox;
	
	virtual void Update(float deltaTime);
	//camera tracking
	Scene* pTargetScene = nullptr;
	void SetTargetScene(Scene* _pTargetScene) { pTargetScene=_pTargetScene; }
	void SetWorld(World* _pWorld) { pWorld = _pWorld; }
};

