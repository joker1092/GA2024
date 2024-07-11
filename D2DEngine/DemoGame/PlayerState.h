#pragma once


class FSM;
class PlayerIdle :public FSMState
{
	GameObject* m_pPlayer;
	bool flip = false;
public:
	PlayerIdle(FSM* pOwner, std::string name) :FSMState(pOwner, name) {}
	// FSMState��(��) ���� ��ӵ�
	void Enter() override;
	void Update(float daltatime) override;
	void CheckTransition() override;
	void Exit() override;

	// FSMState��(��) ���� ��ӵ�
	std::string GetName() override;
};


class PlayerMove : public FSMState
{
	GameObject* m_pPlayer;
	bool flip = false;
public:
	PlayerMove(FSM* pOwner, std::string name) :FSMState(pOwner, name) {}
	// FSMState��(��) ���� ��ӵ�
	void Enter() override;
	void Update(float daltatime) override;
	void CheckTransition() override;
	void Exit() override;

	// FSMState��(��) ���� ��ӵ�
	std::string GetName() override;
};

