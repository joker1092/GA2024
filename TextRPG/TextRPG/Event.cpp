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
		cout << "�踦 Ÿ�� ���踦 ���� ���̴� ����� ��ǳ�� ���� ���� ���� ǥ�� �Ǿ����ϴ�." << endl;
		cout << "" << endl;
	case 1:
	{

	}
	case 99:
		cout << "������ ���� �մϴ�." << endl;
	default:
		break;
	}
}


Event::~Event()
{

}