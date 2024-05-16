#pragma once
#include "../../stdafx.h"

#include "../../System/RenderSystem.h"

#include "../Animation.h"
#include "../Bounds.h"
#include "../Vector2.h"
#include "../Collider.h"
//#include "../Event.h"

#include "../../Manager/CResourceManager.h"

// Object.h�� ũ�� ����, ����� ������ ��ü(�÷��̾�), UI�� �������� ���� 
class Event;
class Collider;

enum ObjectStatus {
	OBJECT_STATUS_IDLE,
	OBJECT_STATUS_MOVE,
	OBJECT_STATUS_ATTACK
};

struct AnimationResource;
struct Object
{
	bool m_isActive = true;							// isDead ��� Ȱ�����¸� ��Ÿ��.

	Vector2 m_pos;									// ���� ��ġ	

	Collider* m_collider;							// �浹ó�� 
	// ���� ������Ʈ ���� �� �ݶ��̴��� �����ϴµ� �ݶ��̴� �Ŵ����� ��ϵ� �ݶ��̴��� � ������� ��������
	Bounds m_renderBounds;							// ������ �̹��� ��ǥ

	Vector2 m_moveDir = { 0.0f ,0.0f };
	Vector2 m_moveDirPrev = { 0.0f,0.0f };
	Vector2 m_inputDir;
	ObjectStatus m_status = OBJECT_STATUS_IDLE;	// �÷��̾��� ���� ��Ÿ�� �� ���

	AnimationResource* m_pAnimationResource = nullptr;
	Event* m_Event = nullptr;
	int m_AnimationMotionIndex = -1;
	int m_AnimationFrameIndex = 0;
	float m_AnimationAccTime = 0.0f;
	bool m_AnimationFlip = false;
	

	virtual void Init();
	virtual void Update(float delta);
	virtual void Render(float alpha);
	virtual void SetMotion(int index);
	virtual void UpdateAnimation(float delta);	
	virtual void ChangeStatus(ObjectStatus status);

	Vector2 GetPosition();
	virtual void OnTrigger() = 0;

	friend class Collider;
	friend class CircleCollider;
	friend class RectangleCollider;

	virtual ~Object() {
		if (m_collider != nullptr) {
			delete m_collider;
		}

		if (m_pAnimationResource != nullptr) {
			delete m_pAnimationResource;
		}
	}
};

//struct UIObject : public Object{
//	void Init() override;
//	void Update(float delta) override;
//	void Render()override;
//	void SetMotion(int index)override;
//	void UpdateAnimation(float delta)override;
//	void ChangeStatus(ObjectStatus status)override;
//};

//struct Enemy : public Object {
//	void Init()override;
//	void Update(float delta)override;
//	void Render()override;
//	void SetMotion(int index)override;
//	void UpdateAnimation(float delta)override;
//	void ChangeStatus(ObjectStatus status)override;
//};

//struct Player : public Object {
//	void Init()override;
//	void Update(float delta)override;
//	void Render()override;
//	void SetMotion(int index)override;
//	void UpdateAnimation(float delta)override;
//	void ChangeStatus(ObjectStatus status)override;
//};
