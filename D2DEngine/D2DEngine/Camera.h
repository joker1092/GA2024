#pragma once
#include "framework.h"
#include "Scene.h"
#include "AABB.h"
#include "Component.h"

// ī�޶� Ŭ����
class Camera:public Scene, public Component
{
public:
	Camera();
	virtual ~Camera();

	AABB m_ViewBoundBox;
	AABB* m_pTargetBoundBox = &m_ViewBoundBox;
	D2D_MATRIX_3X2_F mInvertMatrix;
	// ī�޶� ������Ʈ
	virtual void Update(float deltaTime);
	// ī�޶��� �ٿ�� �ڽ��� �����´�.
	AABB* GetViewBoundBox() const { return m_pTargetBoundBox; }
	// ī�޶��� ���� ��ǥ�� �����´�.
	D2D_MATRIX_3X2_F GetCameraMatrix() {
		return D2D1::Matrix3x2F::Scale(vRelativeScale.x, vRelativeScale.y) *
			D2D1::Matrix3x2F::Rotation(fRelativeRotation) *
			D2D1::Matrix3x2F::Translation(vRelativeLcation.x, vRelativeLcation.y);
	}
	
	// ī�޶��� ������� �����´�.
	D2D_MATRIX_3X2_F GetInvertMatrix() { return mInvertMatrix; }
};

