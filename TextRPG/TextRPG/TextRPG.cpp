#include "Fraemwork.h"

int start() {
	int s;
	while (1)
	{
		printf("Text RPG");
		printf("숫자 입력 (1:게임 시작, 0:종료)");
		scanf_s("%d", &s);
		if (s == 1) {
			return 1;
		}
		else if (s == 0) {
			return 0;
		}
		else {
			continue;
		}
	}
}

int main()
{
	
	int s = start();
	if (s == 0) {
		return 0;
	}

	GamePlay* CGame = new GamePlay();

	/*int a=-1;
	char text[]="";*/
	while (true) {
		/*a=CGame->processInput(text);*/
		CGame->update();
		CGame->render();
	}

	return 0;
}

