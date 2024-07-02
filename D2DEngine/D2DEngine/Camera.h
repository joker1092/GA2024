#pragma once
#include "framework.h"
#include "Scene.h"
#include "AABB.h"
#include "Component.h"

// 카메라 클래스
class Camera:public Scene, public Component
{
public:
	Camera();
	virtual ~Camera();

	AABB m_ViewBoundBox;
	AABB* m_pTargetBoundBox = &m_ViewBoundBox;
	D2D_MATRIX_3X2_F mInvertMatrix;
	// 카메라 업데이트
	virtual void Update(float deltaTime);
	// 카메라의 바운딩 박스를 가져온다.
	AABB* GetViewBoundBox() const { return m_pTargetBoundBox; }
	// 카메라의 월드 좌표를 가져온다.
	D2D_MATRIX_3X2_F GetCameraMatrix() {
		return D2D1::Matrix3x2F::Scale(vRelativeScale.x, vRelativeScale.y) *
			D2D1::Matrix3x2F::Rotation(fRelativeRotation) *
			D2D1::Matrix3x2F::Translation(vRelativeLcation.x, vRelativeLcation.y);
	}
	
	// 카메라의 역행렬을 가져온다.
	D2D_MATRIX_3X2_F GetInvertMatrix() { return mInvertMatrix; }
};

