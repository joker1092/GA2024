#pragma once
#include "framework.h"
#include "Scene.h"
#include <string>
class BitmapScene :
    public Scene
{
	D2DRenderer* pRender;
	std::wstring wstrFileName;
	ID2D1Bitmap* pBitmap = nullptr;
public:
    BitmapScene();
	virtual ~BitmapScene();
	
	bool Load(const std::wstring& strFileName);
	void Update();
	void Render();
};

