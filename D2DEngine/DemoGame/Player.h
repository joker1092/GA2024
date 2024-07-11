#pragma once
#include "Charector.h"

//GameObject�� ��� ���� Charector�� ��ӹ��� �÷��̾� Ŭ����
class InputSystem;
class Player :   public Charector
{
	AnimationScene* PlayerTop; //�÷��̾� ��ü �ִϸ��̼�
	AnimationScene* PlayerBottom; //�÷��̾� ��ü �ִϸ��̼�
	PlayerFSM* pPlayerFSM;
public:
	InputSystem* pInput;
	bool flip = false;
	Player(); 
	virtual ~Player() = default;
	void PlayerInit(InputSystem* in);
	virtual void Update(float deltaTime);
};

