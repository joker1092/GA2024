#pragma once
#include "framework.h"
#include <list>
#include "AnimationAsset.h"



class ResouceManager
{
private:
	std::list < std::pair<const wchar_t*, AnimationAsset*>> m_SharingAnimationAssets;
	std::list < std::pair<const wchar_t*, ID2D1Bitmap*>> m_SharingBitmap;
	bool CreateSharingAnimationAsset(const wchar_t* strFilePath);
	bool CreateSharingBitmapFromFile(const wchar_t* strFilePath);
	void ReleaseSharingAnimationAsset(AnimationAsset*);
	void ReleaseSharingAnimationAsset(ID2D1Bitmap*);
};

