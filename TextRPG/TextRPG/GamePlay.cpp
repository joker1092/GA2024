#include "Fraemwork.h"
#include "GamePlay.h"
#include "Event.h"

GamePlay::GamePlay()
{
	state = 0;
	char text[100] = "�����������մϴ�.";
	textprt = text;
	//printf(text);
	
}

int GamePlay::processInput(char text[])
{
	printf(text);
	int i;
	scanf_s("%d", &i);
	return i;
}


int GamePlay::update()
{
	Event* Gevent = new Event();
	int a = processInput(textprt);
	state = Gevent->resultEvent(state,a);
	delete Gevent;
	return 0;
}

void GamePlay::render()
{
	Event* Gevent = new Event();
	char* textprt2 = Gevent->stateEvent(state);
	// ~~~
	delete textprt2;

	// ������ != �����Ҵ�  *

	delete Gevent;
}


GamePlay::~GamePlay()
{

}