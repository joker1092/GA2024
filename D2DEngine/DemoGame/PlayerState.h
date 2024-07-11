#pragma once


class FSM;
class PlayerIdle :public FSMState
{
	GameObject* m_pPlayer;
	bool flip = false;
public:
	PlayerIdle(FSM* pOwner, std::string name) :FSMState(pOwner, name) {}
	// FSMState을(를) 통해 상속됨
	void Enter() override;
	void Update(float daltatime) override;
	void CheckTransition() override;
	void Exit() override;

	// FSMState을(를) 통해 상속됨
	std::string GetName() override;
};


class PlayerMove : public FSMState
{
	GameObject* m_pPlayer;
	bool flip = false;
public:
	PlayerMove(FSM* pOwner, std::string name) :FSMState(pOwner, name) {}
	// FSMState을(를) 통해 상속됨
	void Enter() override;
	void Update(float daltatime) override;
	void CheckTransition() override;
	void Exit() override;

	// FSMState을(를) 통해 상속됨
	std::string GetName() override;
};

