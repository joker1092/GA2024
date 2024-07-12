#include "BitmapScene.h"

BitmapScene::BitmapScene()
{
	pRM = ResourceManager::pInstance;
}

BitmapScene::~BitmapScene()
{
	/*if (pBitmap)
	{
		pBitmap->Release();
		pBitmap = nullptr;
	}*/
	pRM->ReleaseD2DBitmap(wsBitmapFilePath);
}

bool BitmapScene::LoadD2DBitmap(const std::wstring strFilePath)
{

	if (!pRM->CreateD2DBitmapFrmaFile(strFilePath, &pBitmap))
	{
		return false;
	}
	

	wsBitmapFilePath = strFilePath;
	
	return true;
}

void BitmapScene::Update(float deltaTime)
{
	UpdateTrasnform();
}

void BitmapScene::Render(ID2D1RenderTarget* pRenderTarget)
{
	if (pBitmap == nullptr)return;
	width = pBitmap->GetSize().width;
	height = pBitmap->GetSize().height;
	D2D1_MATRIX_3X2_F m_ScreenTransform = D2D1::Matrix3x2F::Scale(1.0f, -1.0f) * D2D1::Matrix3x2F::Translation(0.0f, D2DRender::Instance->GetClientSize().height);
	D2D1_MATRIX_3X2_F Transform = D2D1::Matrix3x2F::Scale(1.0f, -1.0f) * m_WorldTransform * pD2DRender->m_CameraTransform * m_ScreenTransform;
	
	pRenderTarget->SetTransform(Transform);
	pRenderTarget->DrawBitmap(pBitmap, {0,0,width,height});
}
