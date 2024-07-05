#pragma once

//전체 리소스 관리 클래스
class D2DRender;
class AnimationAsset;
class ResouceManger
{
static ResouceManger* m_pInstance;

//비트맵 정보를 담는 맵
std::map<std::wstring, ID2D1Bitmap*> m_BitmapMap;
//애니메이션 정보를 담는 맵
std::map<std::wstring, AnimationAsset*> m_AnimationMap;
//todo: 추가적인 리소스를 담을 맵을 선언한다.

public:
		ResouceManger();
		~ResouceManger();
		static ResouceManger* GetInstance();
		static void ReleaseInstance();
		//file로부터 비트맵 형식을 로드하여 맵에 저장하고 해당 비트맵의 주소를 반환하는 함수
		ID2D1Bitmap* LoadBitmapFromFile(const std::wstring& _fileName);
		//file로부터 애니메이션 정보를 로드하여 맵에 저장하고 해당 애니메이션의 주소를 반환하는 함수
		AnimationAsset* LoadAnimationFromFile(const std::wstring& _fileName);
		bool AnimationFromCSV(const std::wstring& filename, AnimationAsset**);

};

