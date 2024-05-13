#pragma once
#include "../stdafx.h"
//#include "../Animation.h"

class CResourceManager
{
	//Todo:
	//현제 Gdiplus::Bitmap* 에 대한 map 만 만들어놓았음 animation과 sound 그외 필요시 추가 구현 필요
private:
	static CResourceManager* instance;
	//bitmap* 담을 맵 <key 값, 내용물> 을 담아서 쓸수 있음 
	std::map<std::wstring, Gdiplus::Bitmap*> m_mapBitmap;
	//std::map<std::wstring, AnimationResource*> m_mapAnimation;

public:
	CResourceManager();
	~CResourceManager();
	static CResourceManager* GetInstance();
	static void DestroyInstance();
	//찾기 불러오기 Load시 위 map에 담겨있는지도 판단 하여 있으면 있는 내용물을 없으면 bitmap*로 파일을 불러오라 사용
	Gdiplus::Bitmap* LoadBitmapResouce(const std::wstring& _strkey, const std::wstring& _path);
	Gdiplus::Bitmap* FindBitmapResouce(const std::wstring& _strkey);
	//AnimationResource* LoadAnimationResouce(const std::wstring& _strkey, const std::wstring& _path);
	//AnimationResource* FindAnimationResouce(const std::wstring& _strkey);
	//void setAnimationMotion(const std::wstring& _strkey, const std::wstring& _path, bool IsLoop = true);
};

