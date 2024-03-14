#pragma once

class GamePlay
{
public:
	GamePlay();
	~GamePlay();

	int processInput();
	int update();
	void render();

private:
	int state;
};

