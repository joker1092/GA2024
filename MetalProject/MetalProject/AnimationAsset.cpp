#include "pch.h"
#include "AnimationAsset.h"


AnimationAsset::AnimationAsset()
{
	//생성시 기본 사이즈 10으로 설정
	animations.resize(10);
}

AnimationAsset::~AnimationAsset()
{
	//애니메이션 정보 삭제

}

void AnimationAsset::Load(const wchar_t* _fileName)
{

}

const AnimationAsset::AnimationInfo& AnimationAsset::GetAnimationInfo(const std::wstring& _name)
{
	// TODO: 여기에 return 문을 삽입합니다.
}

void AnimationAsset::LoadTexture(const wchar_t* _fileName)
{
	//파일명으로 비트맵 로드

}

void AnimationAsset::LoadAnimationInfo(const wchar_t* _fileName)
{
}
