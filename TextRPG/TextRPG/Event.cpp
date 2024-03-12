#include "Fraemwork.h"
#include "Event.h"

Event::Event()
{
	
}

int Event::resultEvent(int state, int select) {
	switch (state)
	{	
	case 0:
		
	default:
		break;
	}

	return 1;
}

char* Event::stateEvent(int state) {
	/*char* textptr = new char;
	textptr = "asdf";
	switch (state)
	{
	case 0:

	default:
		break;
	}

	return textprt;*/

	char t1[] = "!";
	// 현재 상태 : ~~~'
	int preStringLength = 12;
	char prestateStr[] = "현재 상태 : ";
	int postStringLength = 7;
	char poststateStr[] = "입니다.";
	const char* stateStr="";
	int length;
	switch (state)
	{
	case 0:
		stateStr = "hi";
		length = 2;
		break;
	case 1:
		break;
	default:
		break;
	}
	int resultLength = preStringLength + postStringLength + length + 1;

	char* resultStateStr = new char[resultLength];

	for (int i = 0; i < preStringLength; ++i) {
		resultStateStr[i] = prestateStr[i];
	}
	for (int i = preStringLength; i < preStringLength + length; ++i) {
		std::cout << stateStr[i];
		resultStateStr[i] = stateStr[i];
	}
	for (int i = preStringLength + length; i < preStringLength + postStringLength + length; ++i) {
		resultStateStr[i] = poststateStr[i];
	}

	return resultStateStr;
}


Event::~Event()
{
}