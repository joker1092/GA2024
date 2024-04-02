#pragma once
#include <Windows.h>

namespace Time {

	void InitTime();
	void UpdateTime();
	ULONGLONG GetDeltaTime();
}