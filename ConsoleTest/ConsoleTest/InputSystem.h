#pragma once
namespace input
{
	const int ESCAPE_KEY_INDEX = 0;
	const int LEFT_KEY_INDEX = 1;
	const int RIGHT_KEY_INDEX = 2;
	const int UP_KEY_INDEX = 3;
	const int DOWN_KEY_INDEX = 4;

	const int MAX_KEY = 5;

	void Set(const int keyIdx, bool bOn);

	bool IsLeftKeyOn();
	bool IsRightKeyOn();
	bool IsUpKeyOn();
	bool IsDownKeyOn();

	void UpdateInput();
};

