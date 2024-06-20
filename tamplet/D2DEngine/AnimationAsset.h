#pragma once

#include "ReferenceCounter.h"

struct FRAME_INFO {
	D2D1_RECT_F sourceRect;
	D2D1_POINT_2F pCenter;
	float renderTime;
};

class AnimationAsset:public ReferenceCounter
{
public:
	std::wstring  strBitmapFilePath;
	ID2D1Bitmap* pBitmap=nullptr;
	std::vector<std::vector<FRAME_INFO>> Animations;
	bool SetAnimationImage(const wchar_t* strBitmapImage);
	bool setAnimation(const wchar_t* strBitmapFilePath);
	~AnimationAsset();
private:
};