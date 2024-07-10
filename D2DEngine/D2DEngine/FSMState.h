#pragma once

//���ѻ��� �ӽ�(Finite State Machine)�� ������ ���� ����(State)�� �θ� �Ǵ� �߻�Ŭ����

class FSM;
class FSMState
{
public:
	FSMState(FSM* pOwner, std::string name) : m_pOwnerFSM(pOwner), m_Name(name) {}
	virtual ~FSMState() {};

	FSM* m_pOwnerFSM; //�� ���¸� �����ϰ� �ִ� FSM
	std::string m_Name; //������ �̸�

	//������ ����, ������Ʈ, ��ȯ, ���� �Լ�
	virtual void Enter() = 0;
	virtual void Update(float daltatime) = 0;
	virtual void CheckTransition() = 0;
	virtual void Exit() = 0;
	virtual std::string GetName() = 0;
};

