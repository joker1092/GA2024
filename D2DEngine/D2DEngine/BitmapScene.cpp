#include "BitmapScene.h"

BitmapScene::BitmapScene()
{
	pRM = ResourceManager::pInstance;
}

BitmapScene::~BitmapScene()
{
	if (pBitmap)
	{
		pBitmap->Release();
		pBitmap = nullptr;
	}
	
}

bool BitmapScene::LoadD2DBitmap(const std::wstring strFilePath,D2DRender* pRender)
{
	/*HRESULT hr;
	hr = pRender->D2DBitmapFromFile(strFilePath.c_str(), &pBitmap);
	if (FAILED(hr))
	{
		return false;
	}*/

	if (!pRM->CreateD2DBitmapFrmaFile(strFilePath, &pBitmap))
	{
		return false;
	}
	

	D2D1_SIZE_U szu = pBitmap->GetPixelSize();
	pCentorPoint = { szu.width / 2.0f,(float)szu.height / 2.0f };

	wsBitmapFilePath = strFilePath;

	return true;
}

void BitmapScene::Update()
{
	UpdateTrasform();
}

void BitmapScene::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	if (pBitmap == nullptr)return;
	pRenderTarget->SetTransform(mWorldTransform);
	pRenderTarget->DrawBitmap(pBitmap);
}
