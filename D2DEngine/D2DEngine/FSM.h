#pragma once
#include "Component.h"

//���ѻ��¸ӽ�
//������Ʈ�� �����Ǿ� ���¸� �����ϴ� ������Ʈ
//���µ��� �߰��ϰ� ��ȯ�ϴ� ����� ����
class FSMState;
class FSM : public Component
{
public:
	FSM() = default;
	virtual ~FSM();
protected:
	std::map<std::string, FSMState*> m_vStates; //���µ��� ������ ��
	FSMState* m_pCurrentState = nullptr; //���� ����
	FSMState* m_pNextState =nullptr; //���� ����

	virtual void Update(float deltaTime);
	void setNextState(std::string nextStateName); //���� ���·� ��ȯ
	
	//State�� �����ϰ� �ʿ� �����ϴ� �Լ�
	template<typename T>//T�� FSMState�� ��ӹ��� Ŭ����
	void createState(std::string SteatName) {
		T* pState = new T(this, SteatName);
		m_vStates.insert(std::make_pair(pState->GetName(), pState));
	}
};

