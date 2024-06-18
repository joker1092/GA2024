#pragma once
#include "../D2DEngine/WinGameApp.h"
#include "../D2DEngine/BitmapScene.h"
#include "../D2DEngine/AnimationInstance.h"
class DemoGameApp : public WinGameApp {
public:
	virtual void Initialize(HINSTANCE hInstance, LPCTSTR appName) override;
	// WinGameApp을(를) 통해 상속됨
	void Render(D2DRenderer* Render) override;

	// WinGameApp을(를) 통해 상속됨
	void Update(InputManager* Input) override;

	virtual void Uninitialize() override;
private:
	//ID2D1Bitmap* pBitmap = nullptr;
	float rotate = 0;

	BitmapScene m_Sun;
	BitmapScene m_Earth;
	BitmapScene m_Moon;
	//AnimationInstance anione;

	D2D_MATRIX_3X2_F g_matWorldScale = D2D1::Matrix3x2F::Identity();
	D2D_MATRIX_3X2_F g_matWorldRotation = D2D1::Matrix3x2F::Identity();
	D2D_MATRIX_3X2_F g_matWorldTranslation = D2D1::Matrix3x2F::Identity();

	D2D_MATRIX_3X2_F g_matWorld = D2D1::Matrix3x2F::Identity(); // 월드 좌표계 변환을 위한 행렬

	D2D_SIZE_U g_ScreenSize;
	D2D_VECTOR_2F g_posCamera = { 0.0f, 0.0f };
	D2D_MATRIX_3X2_F g_matCameraInv = D2D1::Matrix3x2F::Identity();
};


