#pragma once
#include "../D2DEngine/FSMState.h"

class World;
class FSM;
class GameObject;
class BodyIdle : public FSMState
{
	GameObject* m_pPlayer;
	bool flip = false;
	//bool isWeapon = false; //���⸦ ��� �ִ��� ���� //PlayerObject�� �߰� ���ɼ� ����
	public:
		BodyIdle(FSM* pOwner, std::string name) :FSMState(pOwner, name) {}
		// FSMState��(��) ���� ��ӵ�
		void Enter() override;
		void Update(float daltatime) override;
		void CheckTransition() override;
		void Exit() override;
			
		// FSMState��(��) ���� ��ӵ�
		std::string GetName() { return m_Name; }
};

class BodyMove : public FSMState
{
	GameObject* m_pPlayer;
	bool flip = false;
	public:
		BodyMove(FSM* pOwner, std::string name) :FSMState(pOwner, name) {}
		// FSMState��(��) ���� ��ӵ�
		void Enter() override;
		void Update(float daltatime) override;
		void CheckTransition() override;
		void Exit() override;
			
		// FSMState��(��) ���� ��ӵ�
		std::string GetName() { return m_Name; }
};

class BodyJump : public FSMState
{
	GameObject* m_pPlayer;
	bool flip = false;
	public:
		BodyJump(FSM* pOwner, std::string name) :FSMState(pOwner, name) {}
		// FSMState��(��) ���� ��ӵ�
		void Enter() override;
		void Update(float daltatime) override;
		void CheckTransition() override;
		void Exit() override;
			
		// FSMState��(��) ���� ��ӵ�
		std::string GetName() { return m_Name; }
};

class BodyAttack : public FSMState
{
	World* m_pWorld;
	GameObject* m_pPlayer;
	bool flip = false;
	public:
		BodyAttack(FSM* pOwner, std::string name) :FSMState(pOwner, name) {}
		// FSMState��(��) ���� ��ӵ�
		void Enter() override;
		void Update(float daltatime) override;
		void CheckTransition() override;
		void Exit() override;
			
		// FSMState��(��) ���� ��ӵ�
		std::string GetName() { return m_Name; }
};

class BodyDead : public FSMState
{
	GameObject* m_pPlayer;
	bool flip = false;
public:
	BodyDead(FSM* pOwner, std::string name) :FSMState(pOwner, name) {}
	// FSMState��(��) ���� ��ӵ�
	void Enter() override;
	void Update(float daltatime) override;
	void CheckTransition() override;
	void Exit() override;

	// FSMState��(��) ���� ��ӵ�
	std::string GetName() { return m_Name; }
};