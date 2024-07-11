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
	pRenderTarget->SetTransform(m_WorldTransform);
	pRenderTarget->DrawBitmap(pBitmap);
}
