#pragma once
#include "Component.h"
//유한상태머신
//오브젝트에 부착되어 상태를 관리하는 컴포넌트
//상태들을 추가하고 전환하는 기능을 제공
class FSMState;
class FSM : public Component
{
public:
	FSM() = default;
	virtual ~FSM();
protected:
	std::map<std::string, FSMState*> m_vStates; //상태들을 저장할 맵
	FSMState* m_pCurrentState = nullptr; //현재 상태
	FSMState* m_pNextState =nullptr; //다음 상태

	virtual void Update(float deltaTime);
	void setNextState(std::string nextStateName); //다음 상태로 전환
	
	//State를 생성하고 맵에 저장하는 함수
	//T는 FSMState를 상속받은 클래스
	//template 함수로 구현되어 있어서 FSMState를 상속받은 클래스만 State를 생성할 수 있다.
	template<typename T, typename = std::enable_if_t<std::is_base_of<FSMState,T>::value>>
	void createState(std::string StateName) {
		T* pState = new T(this, StateName);
		m_vStates.insert(std::make_pair(pState->GetName(), pState));
	}
};

