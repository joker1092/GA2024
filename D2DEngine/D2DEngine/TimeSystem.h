#pragma once
#include "framework.h"
class TimeSystem
{
	LARGE_INTEGER previousTime = { 0 };
	LARGE_INTEGER currentTime = { 0 };
	LARGE_INTEGER frequency = { 0 };

	float deltaTime = 0;
	//float timeScale = 1.f;
	float timeScale = 1.f;
	//float timeScale2 = 1.f;
public:
	void InitTime();
	void UpdateTime();

	void SetTimeScale(float _timeScale);

	const float GetFrameRate();
	const float GetDeltaTime();
	const float GetUnscaleDeltaTime();
	const float GetTimeScale();
};
