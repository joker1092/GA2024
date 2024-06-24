#pragma once
#include "framework.h"
#include "D2DRender.h"

class ResourceManager
{
public:
	ResourceManager();
	ResourceManager(D2DRender* pRender);
	~ResourceManager();

	static ResourceManager* pInstance;

	D2DRender* pRender;

	std::map<std::wstring, ID2D1Bitmap*> mBitmapMap;

	bool CreateD2DBitmapFrmaFile(std::wstring wstrFilePath, ID2D1Bitmap** bitmap);
	void ReleaseD2DBitmap(std::wstring wstrFilePath);
};

