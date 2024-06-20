#include "pch.h"
#include "ResouceManager.h"

bool ResouceManager::CreateSharingAnimationAsset(const wchar_t* strFilePath)
{
	return false;
}

bool ResouceManager::CreateSharingBitmapFromFile(const wchar_t* strFilePath)
{
	return false;
}

void ResouceManager::ReleaseSharingAnimationAsset(AnimationAsset*)
{
}

void ResouceManager::ReleaseSharingAnimationAsset(ID2D1Bitmap*)
{
}
