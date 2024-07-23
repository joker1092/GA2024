#pragma once
#include "Charector.h"

//GameObject�� ��� ���� Charector�� ��ӹ��� �÷��̾� Ŭ����
class InputSystem;
class PlayerBodyScene;
class PlayerWorkScene;
class BoxCollider;
class PlayerBodyFSM;
class PlayerWorkFSM;
class FireScene;
class Player :   public Charector
{
	PlayerBodyScene* PlayerTop; //�÷��̾� ��ü �ִϸ��̼�
	PlayerWorkScene* PlayerBottom; //�÷��̾� ��ü �ִϸ��̼�
	BoxCollider* PlayerBox; //�÷��̾� �ڽ� �ݶ��̴�
	//PlayerNotify* pPlayerNotify;
	
	//PlayerFSM* pPlayerFSM;
	PlayerBodyFSM* pPlayerBodyFSM;
	PlayerWorkFSM* pPlayerWorkFSM;

	bool isDead = false; //�׾����� Ȯ��
public:
	FireScene* pFireScene; //�÷��̾� �� �߻� ��
	float fireDelay = 0.0f; //�� �߻� ������
	float delay = 0.0f; //�� �߻� ������
	InputSystem* pInput;
	bool flip = false;
	Player(); 
	virtual ~Player() = default;
	void PlayerInit(InputSystem* in);
	virtual void Update(float deltaTime);
	void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void SetIsDead(bool dead) { isDead = dead; }
	bool GetIsDead() { return isDead; }
	void setDelay(float d) { delay = d; }
};

