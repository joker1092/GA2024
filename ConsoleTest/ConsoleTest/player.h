#pragma once
#include <Windows.h>

namespace Player {
	void setPrePosition(COORD coord);
	void setCurPosition(COORD coord);
	COORD getPrePosion();
	COORD getCurPosion();
}