#pragma once
#include "../D2DEngine/WinGameApp.h"
class DemoGameApp : public WinGameApp {
public:

private:
	ID2D1Bitmap* pBitmap = nullptr;

	D2D_MATRIX_3X2_F g_matWorldScale = D2D1::Matrix3x2F::Identity();
	D2D_MATRIX_3X2_F g_matWorldRotation = D2D1::Matrix3x2F::Identity();
	D2D_MATRIX_3X2_F g_matWorldTranslation = D2D1::Matrix3x2F::Identity();

	D2D_MATRIX_3X2_F g_matWorld = D2D1::Matrix3x2F::Identity(); // ���� ��ǥ�� ��ȯ�� ���� ���

	D2D_SIZE_U g_ScreenSize;
	D2D_VECTOR_2F g_posCamera = { 0.0f, 0.0f };
	D2D_MATRIX_3X2_F g_matCameraInv = D2D1::Matrix3x2F::Identity();

	// WinGameApp��(��) ���� ��ӵ�
	void Render(D2DRenderer* Render) override;

	// WinGameApp��(��) ���� ��ӵ�
	void Update(InputManager* Input) override;
};


