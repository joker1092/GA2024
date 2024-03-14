#include "Fraemwork.h"
#include "GamePlay.h"
#include "Event.h"
enum state {
	quit=99,
	wrongsel=0
};
GamePlay::GamePlay()
{
	state = 0;
}

int GamePlay::processInput()
{
	int i;
	scanf_s("%d", &i);

	return i;
}


int GamePlay::update()
{
	Event* Gevent = new Event();
	int a = processInput();
	int tmpset = Gevent->resultEvent(state, a);
	while (tmpset == 1)
	{
		cout << "잘 못 입력 하셨습니다. 다시 입력 해주세요." << endl;
		a = processInput();
		tmpset = Gevent->resultEvent(state, a);
	}

	state = tmpset;
	cout << state << endl;
	delete Gevent;
	return 0;
}

void GamePlay::render()
{
	Event* Gevent = new Event();
	cout << state << endl;
	Gevent->stateEvent(state);
	

	delete Gevent;
}


GamePlay::~GamePlay()
{

}