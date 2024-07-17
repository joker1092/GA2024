#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/AnimationScene.h"
#include "../D2DEngine/AnimationAsset.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/SideMovement.h"
#include "EnemyRifleFSM.h"
#include "PlayerFSM.h"

//GameObject�� ��� ���� �ɸ��� Ŭ����
class Charector :   public GameObject
{
	public:
		AnimationScene* pAnimationSc;
		SideMovement* pMovement;
	Charector();
	virtual ~Charector() = default;
	virtual void Update(float deltaTime);
	void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
};

