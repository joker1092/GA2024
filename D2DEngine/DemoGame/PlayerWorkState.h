#pragma once
#include "../D2DEngine/FSMState.h"

class FSM;
class GameObject;
class WorkIdle : public FSMState
{
	GameObject* m_pPlayer;
	bool flip = false;
public:
	WorkIdle(FSM* pOwner, std::string name) :FSMState(pOwner, name) {}
	// FSMState을(를) 통해 상속됨
	void Enter() override;
	void Update(float daltatime) override;
	void CheckTransition() override;
	void Exit() override;

	// FSMState을(를) 통해 상속됨
	std::string GetName() { return m_Name; }
};

class WorkMove : public FSMState
{
	GameObject* m_pPlayer;
	bool flip = false;
public:
	WorkMove(FSM* pOwner, std::string name) :FSMState(pOwner, name) {}
	// FSMState을(를) 통해 상속됨
	void Enter() override;
	void Update(float daltatime) override;
	void CheckTransition() override;
	void Exit() override;

	// FSMState을(를) 통해 상속됨
	std::string GetName() { return m_Name; }
};

class WorkJump : public FSMState
{
	GameObject* m_pPlayer;
	bool flip = false;
public:
	WorkJump(FSM* pOwner, std::string name) :FSMState(pOwner, name) {}
	// FSMState을(를) 통해 상속됨
	void Enter() override;
	void Update(float daltatime) override;
	void CheckTransition() override;
	void Exit() override;

	// FSMState을(를) 통해 상속됨
	std::string GetName() { return m_Name; }
};

class WorkMoveJump : public FSMState
{
	GameObject* m_pPlayer;
	bool flip = false;
public:
	WorkMoveJump(FSM* pOwner, std::string name) :FSMState(pOwner, name) {}
	// FSMState을(를) 통해 상속됨
	void Enter() override;
	void Update(float daltatime) override;
	void CheckTransition() override;
	void Exit() override;

	// FSMState을(를) 통해 상속됨
	std::string GetName() { return m_Name; }
};

class WorkDead : public FSMState
{
	GameObject* m_pPlayer;
	bool flip = false;
public:
	WorkDead(FSM* pOwner, std::string name) :FSMState(pOwner, name) {}
	// FSMState을(를) 통해 상속됨
	void Enter() override;
	void Update(float daltatime) override;
	void CheckTransition() override;
	void Exit() override;

	// FSMState을(를) 통해 상속됨
	std::string GetName() { return m_Name; }
};

