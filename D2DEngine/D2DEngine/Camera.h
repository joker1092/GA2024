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
	bool isFixed = false; // ī�޶� �����Ǿ� �ִ��� ����
	D2D1_VECTOR_2F m_FixedLocation; // ���� ��ġ
	virtual void Update(float deltaTime);
	//camera tracking
	Scene* pTargetScene = nullptr;
	void SetTargetScene(Scene* _pTargetScene) { pTargetScene=_pTargetScene; }
	void SetWorld(World* _pWorld) { pWorld = _pWorld; }
	
	//������Ʈ�� ī�޶� ���� ������ �������� �Ҷ� ������ �� �ϰ� �Ϸ��� ���
	//ī�޶󿡼� �����ϴ°��� �´°� ������Ʈ���� ���� �ϴ� ���� �´°�?
	void ObjectClampToCamera(Scene* pScene);
	bool ContainsVector(D2D1_VECTOR_2F v);
	D2D1_VECTOR_2F VectorClamp(D2D1_VECTOR_2F v);

	//TargetScene�� ����ٴϴ� ī�޶� Ʈ���ſ� ���Ͽ� ��� ��ġ�� ���� �ϴ� ����� �ִ°�?
	//�ϴ� �̺�Ʈ �ڵ��� ����� ����
	//2���� �ڵ��� �ʿ�
	//1.��ġ ���� �޾� ī�޶� �����ϴ� �ڵ�
	//2.Ʈ���� �̺�Ʈ�� �޾� �ٽ� target�� ����ٴϴ� �ڵ�
	
	void SetFixedLocation(D2D1_VECTOR_2F _FixedLocation) {
		isFixed=true;
		m_FixedLocation = _FixedLocation; 
	}

	void ReleaseFixedLocation() {
		isFixed = false;
	}
};




