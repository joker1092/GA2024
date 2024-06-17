#include "BitmapScene.h"

BitmapScene::BitmapScene()
{
	pRender = D2DRenderer::GetInstance();
}

BitmapScene::~BitmapScene()
{
	if (pBitmap) {
		pBitmap->Release();
		pBitmap = nullptr;
	}
}

bool BitmapScene::Load(const std::wstring& strFileName)
{
	HRESULT hr = S_OK;
	hr = pRender->CreateD2DBitmapFromFile(strFileName.c_str(), &pBitmap);
	//D2D1_SIZE_F szf = pBitmap->GetSize();
	D2D1_SIZE_U szu = pBitmap->GetPixelSize();
	pCentorPoint = { szu.width / 2.0f,(float)szu.height / 2.0f };
	return false;
}

void BitmapScene::Update()
{
	UpdateTransform();
}

void BitmapScene::Render()
{
	pRender->DrawBitmap(pBitmap, mWorldTransform);
}


