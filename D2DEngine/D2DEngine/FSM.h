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
	//T�� FSMState�� ��ӹ��� Ŭ����
	//template �Լ��� �����Ǿ� �־ FSMState�� ��ӹ��� Ŭ������ State�� ������ �� �ִ�.
	template<typename T, typename = std::enable_if_t<std::is_base_of<FSMState,T>::value>>
	void createState(std::string StateName) {
		T* pState = new T(this, StateName);
		m_vStates.insert(std::make_pair(pState->GetName(), pState));
	}
};

