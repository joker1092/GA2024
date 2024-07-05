
#include "pch.h"
#include "ResouceManger.h"
#include "D2DRender.h"
#include "AnimationAsset.h"

ResouceManger* ResouceManger::GetInstance()
{
    static ResouceManger instance;
    return &instance;
}

ID2D1Bitmap* ResouceManger::LoadBitmapFromFile(const std::wstring& _fileName)
{
    // 비트맵 저장 맵에 이미 존재하는지 확인
    std::map<std::wstring, ID2D1Bitmap*>::iterator iter = m_BitmapMap.find(_fileName);
    if (iter != m_BitmapMap.end())
    {
        // 이미 존재하면 해당 비트맵 주소를 반환
        return iter->second;
    }
    // 아닌 경우 D2DRender를 통하여 비트맵을 로드하고 맵에 저장
    D2DRender* render = D2DRender::GetInstance();
    ID2D1Bitmap* bitmap = nullptr;
    // 로드 실패시 assert
    if (render->LoadBitmapFromFile(_fileName.c_str(), &bitmap))
    {
        assert(false); // Add this assert statement
    }
    m_BitmapMap[_fileName] = bitmap;

    return bitmap;
}

AnimationAsset* ResouceManger::LoadAnimationFromFile(const std::wstring& _fileName)
{
    // 애니메이션 저장 맵에 이미 존재하는지 확인
    std::map<std::wstring, AnimationAsset*>::iterator iter = m_AnimationMap.find(_fileName);
    if (iter != m_AnimationMap.end())
	{
		// 이미 존재하면 해당 애니메이션 주소를 반환
		return iter->second;
	}
    // 아닌 경우 애니메이션을 로드하고 맵에 저장
    AnimationAsset* animation;
    //CSV 파일을 통해 애니메이션 정보를 로드
    if (AnimationFromCSV(_fileName, &animation))
    {
        assert(false);
    }
    m_AnimationMap[_fileName] = animation;
    
    return animation;
}

bool ResouceManger::AnimationFromCSV(const std::wstring& filename, AnimationAsset**)
{
    AnimationAsset* animation = new AnimationAsset();
    //CSV 파일 오픈
    std::wifstream file(filename);
    if (!file.is_open())
	{
        return false;
	}
    //wiftream 을 wstringstram으로 변환
    
    //한줄씩 읽어오기
    std::wstring line;
    while (std::getline(file, line))
	{
		//한줄을 ,로 나누어서 정보를 읽어옴
		std::wstringstream wss(line);
		std::wstring name;
		wss >> name;
		//애니메이션 이름이면 애니메이션 정보를 추가
		if (name == L"Animation")
		{
			AnimationAsset::AnimationInfo info;
			wss >> info.name;
			//프레임 정보를 추가
			while (std::getline(file, line))
			{
				std::wstringstream wss(line);
				std::wstring frame;
				wss >> frame;
				if (frame == L"Frame")
				{
					AnimationAsset::FrameInfo frameInfo;
					wss >> frameInfo.left >> frameInfo.top >> frameInfo.right >> frameInfo.bottom >> frameInfo.centerX >> frameInfo.centerY >> frameInfo.duration;
					info.frameInfos.push_back(frameInfo);
				}
				else
				{
					break;
				}
			}
			animation->animations.push_back(info);
		}
	}
   
    
}

