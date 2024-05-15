
#include "TimeSystem.h"


//namespace Time
//{	
//	
//	ULONGLONG previousTime;
//	ULONGLONG currentTime;
//	ULONGLONG deltaTime;
//
//	void InitTime()
//	{
//		previousTime = currentTime = GetTickCount64();
//	}
//
//	void UpdateTime()
//	{
//		previousTime = currentTime;
//
//		currentTime = GetTickCount64();
//
//		deltaTime = currentTime - previousTime;
//	}
//
//	const float GetFrameRate()
//	{
//		if (deltaTime == 0) return 0;
//
//		return ceil(((1000.0f / deltaTime) * 1000) / 1000);
//	}
//
//	const ULONGLONG GetDeltaTime() { return deltaTime; }
//
//}

namespace High_Resolution_Time
{
	LARGE_INTEGER previousTime = { 0 };
	LARGE_INTEGER currentTime = { 0 };
	LARGE_INTEGER frequency = { 0 };

	float deltaTime = 0;
	float timeScale = 1.f;

	void InitTime()
	{
		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&previousTime);
	}

	void UpdateTime()
	{
		QueryPerformanceCounter(&currentTime);

		deltaTime = (currentTime.QuadPart - previousTime.QuadPart) / (frequency.QuadPart / 1000.f); //ms
		previousTime = currentTime;
	}
	void SetTimeScale(float _timeScale) {
		timeScale = _timeScale;
	}

	const float GetFrameRate()
	{
		if (deltaTime == 0) return 0;

		return ceil(((1000.0f / deltaTime) * 1000) / 1000);
	}

	const float GetDeltaTime() { return deltaTime * timeScale; }
}