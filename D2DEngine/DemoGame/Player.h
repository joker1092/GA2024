#pragma once
#include "Charector.h"

//GameObject를 상속 받은 Charector를 상속받은 플레이어 클레스
class InputSystem;
class PlayerBodyScene;
class PlayerWorkScene;
class BoxCollider;
class PlayerBodyFSM;
class PlayerWorkFSM;
class Player :   public Charector
{
	PlayerBodyScene* PlayerTop; //플레이어 상체 애니메이션
	PlayerWorkScene* PlayerBottom; //플레이어 하체 애니메이션
	BoxCollider* PlayerBox; //플레이어 박스 콜라이더
	//PlayerNotify* pPlayerNotify;

	//PlayerFSM* pPlayerFSM;
	PlayerBodyFSM* pPlayerBodyFSM;
	PlayerWorkFSM* pPlayerWorkFSM;

	bool isDead = false; //죽었는지 확인

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
	void SetIsDead(bool dead) { isDead = dead; }
	bool GetIsDead() { return isDead; }
};

