#pragma once
#include "framework.h"


struct FRAME_INFO {
	D2D1_RECT_F sourceRect;
	D2D1_POINT_2F pCenter;
	float renderTime;
};

class AnimationAsset
{
public:
	enum State
	{
		DEATH = 0,
		IDEL,
		ATECK,
		DAMEGE,
		END = 99
	};
	std::wstring  strBitmapFilePath;
	ID2D1Bitmap* pBitmap;
	std::vector<std::vector<FRAME_INFO>> Animations;
	bool SetAnimationImage();
	bool setAnimation(const wchar_t* strBitmapFilePath,State state);
private:
};