#pragma once

//유한상태 머신(Finite State Machine)이 가지고 있을 상태(State)의 부모가 되는 추상클래스

class FSM;
class FSMState
{
public:
	FSMState(FSM* pOwner, std::string name) : m_pOwnerFSM(pOwner), m_Name(name) {}
	virtual ~FSMState() {};

	FSM* m_pOwnerFSM; //이 상태를 소유하고 있는 FSM
	std::string m_Name; //상태의 이름

	//상태의 진입, 업데이트, 전환, 종료 함수
	virtual void Enter() = 0;
	virtual void Update(float daltatime) = 0;
	virtual void CheckTransition() = 0;
	virtual void Exit() = 0;
	virtual std::string GetName() = 0;
};

