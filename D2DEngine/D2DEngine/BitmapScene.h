#pragma once
#include "Scene.h"
#include "D2DRender.h"
#include "ResourceManager.h"

class D2DRender;

class BitmapScene : public Scene
{
public:
	BitmapScene();
	virtual ~BitmapScene();

	std::wstring wsBitmapFilePath;
	ID2D1Bitmap* pBitmap = nullptr;
	ResourceManager* pRM;

	bool LoadD2DBitmap(const std::wstring strFilePath, D2DRender* _pRender);
	void Update();
	void Render(ID2D1HwndRenderTarget* pRenderTarget);
};

