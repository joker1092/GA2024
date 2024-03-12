#pragma once

class GamePlay
{
public:
	GamePlay();
	~GamePlay();

	int processInput(char text[]);
	int update();
	void render();

private:
	int state;
	char* textprt;
	//char text[100];
};

