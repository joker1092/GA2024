#pragma once
#include <Windows.h>

namespace global {
	namespace time {
		ULONGLONG previousTime;
		ULONGLONG currentTime;
		ULONGLONG deltaTime;

		int updateCount;
		int fixedUpdateCount;

		void InitTime() {
			currentTime = previousTime = GetTickCount64();
		}

		void UpdateTime() {
			previousTime = currentTime;
			currentTime = GetTickCount64();

			deltaTime = currentTime - previousTime;
		}

		ULONGLONG GetDeltaTime() {
			return deltaTime;
		}
	};
	COORD prePlayerPos;
	COORD curPlayerPos;

	SMALL_RECT consoleScreenSize;
	SMALL_RECT playerMovableRect = { 4,4,100,20 };

	const int playerMoveSpeed = 200;
};
