#pragma once
#include "../D2DEngine/FSM.h"
//player�� ��ü FSM
class PlayerBodyFSM : public FSM
{
	public:
	PlayerBodyFSM() = default;
	~PlayerBodyFSM() = default;
	void Initialize();
    virtual void Update(float deltaTime);
};

