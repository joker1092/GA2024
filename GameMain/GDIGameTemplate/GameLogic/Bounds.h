#include "Vector2.h"

#pragma once
struct Bounds {
	Vector2 center;
	Vector2 extents;
	Bounds() {
		this->center = { 0.0f, 0.0f };
		this->extents = { 0.0f, 0.0f };
	}
	Bounds(Vector2 center, Vector2 extents) {
		this->center = center;
		this->extents = extents;
	}

	Vector2 size() {
		return extents * 2;
	}

	Vector2 maxPosition() {
		return center + extents;
	}

	Vector2 minPosition() {
		return center - extents;	
	}
};