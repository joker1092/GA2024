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

bool BitmapScene::LoadD2DBitmap(const std::wstring strFilePath,D2DRender* pRender)
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
	UpdateTrasform();
}

void BitmapScene::Render(ID2D1RenderTarget* pRenderTarget)
{
	if (pBitmap == nullptr)return;
	pRenderTarget->SetTransform(mInvertCenterMat * mWorldTransform);
	pRenderTarget->DrawBitmap(pBitmap);
}
