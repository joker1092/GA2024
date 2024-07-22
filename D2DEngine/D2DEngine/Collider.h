#pragma once
#include "Scene.h"


enum class ColliderType
{
	None,
	Circle,
	Box
};

enum class CollisionType 
{
	NoCollision,
	Blockm,
	Overlap
};

class Collider;
class IColliderNotify
{
public:
	virtual void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) = 0;
	virtual void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) = 0;
	virtual void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) = 0;
};

class Collider : public Scene
{
protected:
	CollisionType m_CollisionType = CollisionType::NoCollision;
	ColliderType m_ColliderType = ColliderType::None;
	IColliderNotify* m_pNotify = nullptr;

	std::set<Collider*> m_CollideStateCurr; // 현재 충돌 상태
	std::set<Collider*> m_CollideStatePrev; // 이전 충돌 상태

public:
	Collider() = default;
	~Collider() = default;
	
	//
	CollisionType GetCollisionType() { return m_CollisionType; }
	void SetCollisionType(CollisionType type) { m_CollisionType = type; }
	ColliderType GetColliderType() { return m_ColliderType; }

	void ClearCollideState();

	void SetNotify(IColliderNotify* pNotify) { m_pNotify = pNotify; }

	bool IsEmptyCollideStateCurr() { return m_CollideStateCurr.empty(); }

	void AddCollideStateCurr(Collider* pCollider){ m_CollideStateCurr.insert(pCollider); }
	void ProcessOverlap();
	void ProcessBlock(Collider* pOtherComponent);

	virtual bool IsCollide(Collider* pOtherComponent) = 0;
	virtual void Render(ID2D1RenderTarget* pRenderTarget);
};

