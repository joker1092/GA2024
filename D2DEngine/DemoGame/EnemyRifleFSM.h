#pragma once
#include "../D2DEngine/D2DRender.h"
#include "../D2DEngine/FSM.h"
#include "../D2DEngine/FSMState.h"
class FSMState;
class EnemyRifleFSM :public FSM
{
	public:
	EnemyRifleFSM() = default;
	~EnemyRifleFSM() = default;
	void Initialize();
	void Update(float deltaTime);
	void Release();
};

