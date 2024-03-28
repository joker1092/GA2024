#include "timer.h"

namespace timer {
	ULONGLONG previousTime;
	ULONGLONG currentTime;
	ULONGLONG deltaTime;

	int updateCount;
	int fixedUpdateCount;

	void InitTime() {
		previousTime = currentTime = GetTickCount64();
	}

	void UpdateTime() {
		previousTime = currentTime;
		currentTime = GetTickCount64();
		deltaTime = currentTime - previousTime;
	}

	ULONGLONG GetDeltaTime() {
		return deltaTime;
	}
}