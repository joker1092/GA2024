#pragma once
#include "../D2DEngine/MathHelper.h"

using namespace MathHelper;

class World;
class GameObject;
class Movement;
class Player;
class FSM;
class EnemyRifleIdle : public FSMState
{
	World* m_pWorld =nullptr;
   	GameObject* m_pEnemyRifle = nullptr;
	Player* m_pPlayer = nullptr;
	bool flip = false;
	public:
		EnemyRifleIdle(FSM* pOwner, std::string name) :FSMState(pOwner, name) {}

		void Enter() override;
		void Update(float daltatime) override;
		void CheckTransition() override;
		void Exit() override;

		// FSMState을(를) 통해 상속됨
		std::string GetName() override;
};

class FSM;
class EnemyRifleMove : public FSMState
{
	World* m_pWorld = nullptr;
	GameObject* m_pEnemyRifle = nullptr;
	Player* m_pPlayer = nullptr;
	Movement* movement =nullptr;
	MathHelper::Vector2F m_pPlayerLocation;
	MathHelper::Vector2F m_pEnemyRifleLocation;
	bool flip = false;
public:
	EnemyRifleMove(FSM* pOwner, std::string name) :FSMState(pOwner, name) {}

	void Enter() override;
	void Update(float daltatime) override;
	void CheckTransition() override;
	void Exit() override;

	// FSMState을(를) 통해 상속됨
	std::string GetName() override;
};

class FSM;
class EnemyRifleAttack : public FSMState
{
	World* m_pWorld = nullptr;
	GameObject* m_pEnemyRifle = nullptr;
	Player* m_pPlayer = nullptr;
	Movement* movement = nullptr;
	MathHelper::Vector2F m_pPlayerLocation;
	MathHelper::Vector2F m_pEnemyRifleLocation;
	bool flip = false;
public:
	EnemyRifleAttack(FSM* pOwner, std::string name) :FSMState(pOwner, name) {}

	void Enter() override;
	void Update(float daltatime) override;
	void CheckTransition() override;
	void Exit() override;

	// FSMState을(를) 통해 상속됨
	std::string GetName() override;
};

