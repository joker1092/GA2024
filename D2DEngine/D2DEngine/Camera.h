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
	bool isFixed = false; // 카메라가 고정되어 있는지 여부
	D2D1_VECTOR_2F m_FixedLocation; // 고정 위치
	virtual void Update(float deltaTime);
	//camera tracking
	Scene* pTargetScene = nullptr;
	void SetTargetScene(Scene* _pTargetScene) { pTargetScene=_pTargetScene; }
	void SetWorld(World* _pWorld) { pWorld = _pWorld; }
	
	//오브젝트가 카메라 영역 밖으로 나가려고 할때 나가지 못 하게 하려는 경우
	//카메라에서 구현하는것이 맞는가 오브젝트에서 구현 하는 것이 맞는가?
	void ObjectClampToCamera(Scene* pScene);
	bool ContainsVector(D2D1_VECTOR_2F v);
	D2D1_VECTOR_2F VectorClamp(D2D1_VECTOR_2F v);

	//TargetScene을 따라다니는 카메라가 트리거에 의하여 어느 위치에 고정 하는 방법이 있는가?
	//일다 이벤트 핸들을 만들어 보자
	//2개의 핸들이 필요
	//1.위치 값을 받아 카메라를 고정하는 핸들
	//2.트리거 이벤트를 받아 다시 target을 따라다니는 핸들
	
	void SetFixedLocation(D2D1_VECTOR_2F _FixedLocation) {
		isFixed=true;
		m_FixedLocation = _FixedLocation; 
	}

	void ReleaseFixedLocation() {
		isFixed = false;
	}
};




