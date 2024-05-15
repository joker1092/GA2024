#pragma once
#include "../WinMain.h"
#include "../stdafx.h"
//namespace Time
//{
//	void InitTime();
//
//	void UpdateTime();
//
//	const float GetFrameRate();
//
//	const ULONGLONG GetDeltaTime();
//
//}


namespace High_Resolution_Time
{
	void InitTime();

	void UpdateTime();

	void SetTimeScale(float _timeScale);

	const float GetFrameRate();

	const float GetDeltaTime();
}