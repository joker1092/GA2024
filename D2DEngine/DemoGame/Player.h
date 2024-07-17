#pragma once
#include "Charector.h"

//GameObject�� ��� ���� Charector�� ��ӹ��� �÷��̾� Ŭ����
class InputSystem;
class AnimationScene;
class BoxCollider;
class PlayerNotify;
class Player :   public Charector
{
	AnimationScene* PlayerTop; //�÷��̾� ��ü �ִϸ��̼�
	AnimationScene* PlayerBottom; //�÷��̾� ��ü �ִϸ��̼�
	BoxCollider* PlayerBox; //�÷��̾� �ڽ� �ݶ��̴�
	PlayerNotify* pPlayerNotify;
	PlayerFSM* pPlayerFSM;
public:
	InputSystem* pInput;
	bool flip = false;
	Player(); 
	virtual ~Player() = default;
	void PlayerInit(InputSystem* in);
	virtual void Update(float deltaTime);
	void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
};

