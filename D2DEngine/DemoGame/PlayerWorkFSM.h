#pragma once
#include "../D2DEngine/FSM.h"
//player�� ��ü FSM
class PlayerWorkFSM : public FSM
{
	public:
	PlayerWorkFSM() = default;
	~PlayerWorkFSM() = default;
	void Initialize();
	virtual void Update(float deltaTime);
};

