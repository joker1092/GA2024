#pragma once
#include "../../stdafx.h"

#include "../../System/RenderSystem.h"

#include "../Animation.h"
#include "../Bounds.h"
#include "../Vector2.h"
#include "../Collider.h"
//#include "../Event.h"

#include "../../Manager/CResourceManager.h"

// Object.h는 크게 몬스터, 물고기 건지는 뜰체(플레이어), UI로 구분지을 예정 
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
	bool m_isActive = true;							// isDead 대신 활성상태를 나타냄.

	Vector2 m_pos;									// 현재 위치	

	Collider* m_collider;							// 충돌처리 
	// 만약 오브젝트 삭제 시 콜라이더를 삭제하는데 콜라이더 매니저에 등록된 콜라이더는 어떤 방식으로 삭제할지
	Bounds m_renderBounds;							// 렌더할 이미지 좌표

	Vector2 m_moveDir = { 0.0f ,0.0f };
	Vector2 m_moveDirPrev = { 0.0f,0.0f };
	Vector2 m_inputDir;
	ObjectStatus m_status = OBJECT_STATUS_IDLE;	// 플레이어의 상태 나타낼 때 사용

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
