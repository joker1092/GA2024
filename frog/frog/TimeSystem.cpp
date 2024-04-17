#include "WinApp.h"
#include "TimeSystem.h"
#include <cmath>


void TimeSystem::InitTime() {
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&previousTime);
}

void TimeSystem::UpdateTime() {
	previousTime = currentTime;
	QueryPerformanceCounter(&currentTime);

	deltaTime = (currentTime.QuadPart - previousTime.QuadPart) / (frequency.QuadPart / 1000.0f);
}

const float TimeSystem::GetFrameRate() {
	if (deltaTime == 0) return 0;

	return ceil(((1000.0f / deltaTime) * 1000) / 1000);
}

//const ULONGLONG GetDeltaTime();
const float TimeSystem::GetDeltaTime() {
	return deltaTime;
}