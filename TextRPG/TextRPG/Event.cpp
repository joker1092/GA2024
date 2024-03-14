#include "Fraemwork.h"
#include "Event.h"

Event::Event()
{
	
}

int Event::resultEvent(int state, int select) {
	switch (state)
	{	
	case 0:
	{
		switch (select)
		{
		case 0: {
			return 99;
		}
		case 1: {
			return 2;
		}
		default:
			break;
		}
	}
	default:
		break;
	}
}

void Event::stateEvent(int state) {
	switch (state)
	{
	case 0:
		cout << "배를 타고 세계를 여행 중이던 당신은 폭풍을 만나 낮선 땅에 표류 되었습니다." << endl;
		cout << "" << endl;
	case 1:
	{

	}
	case 99:
		cout << "게임을 종료 합니다." << endl;
	default:
		break;
	}
}


Event::~Event()
{

}