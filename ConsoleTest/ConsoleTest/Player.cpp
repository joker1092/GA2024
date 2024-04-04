#include "player.h"

namespace Player {
	COORD prePosition = { 0,0 };
	COORD curPosition = { 0,0 };

	void setPrePosition(COORD coord) {
		prePosition.X = coord.X;
		prePosition.Y = coord.Y;
	}

	void setCurPosition(COORD coord) {
		curPosition.X = coord.X;
		curPosition.Y = coord.Y;
	}

	COORD getPrePosion() {
		return prePosition;
	}

	COORD getCurPosion() {
		return curPosition;
	}
}
