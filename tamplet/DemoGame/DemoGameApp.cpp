#include "DemoGameApp.h"

void DemoGameApp::Update(InputManager* Input)
{
	
	if (Input->IsKey('A')) {
		g_posCamera.x -= 10;
	}
	if (Input->IsKey('D')) {
		g_posCamera.x += 10;
	}
	if (Input->IsKey('W')) {
		g_posCamera.y -= 10;
	}
	if (Input->IsKey('S')) {
		g_posCamera.y += 10;
	}
	
	
}

void DemoGameApp::Render(D2DRenderer* Render)
{
	std::wstring str;
	str = L"Camera X : " + std::to_wstring(g_posCamera.x) + L" Camera Y : " + std::to_wstring(g_posCamera.y);

	g_matWorldScale = D2D1::Matrix3x2F::Scale(1.0f, 1.0f);
	g_matWorldRotation = D2D1::Matrix3x2F::Rotation(0.0f); // 회전각도
	g_matWorldTranslation = D2D1::Matrix3x2F::Translation(0.0f, 0.0f); // 이동
	g_matWorld = g_matWorldScale * g_matWorldRotation * g_matWorldTranslation;

	// 카메라의 월드위치로 역행렬을 계산하여 카메라 좌표계로 변환하는 행렬
	g_matCameraInv = D2D1::Matrix3x2F::Translation(g_posCamera.x, g_posCamera.y);
	D2D1InvertMatrix(&g_matCameraInv);

	D2D_MATRIX_3X2_F Transform = g_matWorld * g_matCameraInv;
	
	Render->CreateD2DBitmapFromFile(L"../Resource/atk_1.png", &pBitmap);

	Render->RenderSetTransform(Transform);

	D2D_MATRIX_3X2_F pBitmapTransform = D2D1::Matrix3x2F::Translation(200.0f, 200.0f);
	D2D_MATRIX_3X2_F pBitmapRotation = D2D1::Matrix3x2F::Rotation(45.0f);
	D2D_MATRIX_3X2_F pBitmapMatrix = pBitmapTransform * pBitmapRotation;
	Render->DrawBitmap(pBitmap, pBitmapMatrix* Transform);

	Render->PrintMatrix(L"Transform", Transform, 700, 100);

	Render->PrintMatrix(L"g_matWorld", g_matWorld, 1000, 100);
	Render->PrintMatrix(L"g_matCameraInv", g_matCameraInv, 1100, 100);

	WCHAR buffer[256] = { 0 };
	swprintf_s(buffer, L"%.2f, %.2f\n", g_posCamera.x, g_posCamera.y);
	D2D1_RECT_F rect = { 400,400,100,100 };
	wcscat_s(buffer, 256, L"g_posCamera");
	Render->DWDrawText(buffer, rect);
}


