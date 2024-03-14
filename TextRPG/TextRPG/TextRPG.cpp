#include "Fraemwork.h"

void start() {
	cout << "Text RPG" << endl;
	cout << "숫자 입력 (1:게임 시작, 0:종료)" << endl;
}

int main()
{
	
	start();

	GamePlay* CGame = new GamePlay();
	Charecter* NChar = new Charecter();
	
	int state = 0;;
	while (state!=99) {
		/*a=CGame->processInput(text);*/
		state = CGame->update();
		system("cls");
		NChar->statusView(state);
		CGame->render();
	}

	delete NChar;
	delete CGame;

	return 0;
}

