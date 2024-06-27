#pragma once
#include "framework.h"

class Camera
{
	D2D_MATRIX_3X2_F Transform;
public:
	Camera() { Transform = D2D1::Matrix3x2F::Identity(); }
	~Camera() {}
	D2D_MATRIX_3X2_F GetCameraTransform() { return Transform; }
	void CameraUpdate(float deltatime);
	void TreckingTarget();
};

