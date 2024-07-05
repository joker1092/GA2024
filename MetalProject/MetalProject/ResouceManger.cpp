
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
    // ��Ʈ�� ���� �ʿ� �̹� �����ϴ��� Ȯ��
    std::map<std::wstring, ID2D1Bitmap*>::iterator iter = m_BitmapMap.find(_fileName);
    if (iter != m_BitmapMap.end())
    {
        // �̹� �����ϸ� �ش� ��Ʈ�� �ּҸ� ��ȯ
        return iter->second;
    }
    // �ƴ� ��� D2DRender�� ���Ͽ� ��Ʈ���� �ε��ϰ� �ʿ� ����
    D2DRender* render = D2DRender::GetInstance();
    ID2D1Bitmap* bitmap = nullptr;
    // �ε� ���н� assert
    if (render->LoadBitmapFromFile(_fileName.c_str(), &bitmap))
    {
        assert(false); // Add this assert statement
    }
    m_BitmapMap[_fileName] = bitmap;

    return bitmap;
}

AnimationAsset* ResouceManger::LoadAnimationFromFile(const std::wstring& _fileName)
{
    // �ִϸ��̼� ���� �ʿ� �̹� �����ϴ��� Ȯ��
    std::map<std::wstring, AnimationAsset*>::iterator iter = m_AnimationMap.find(_fileName);
    if (iter != m_AnimationMap.end())
	{
		// �̹� �����ϸ� �ش� �ִϸ��̼� �ּҸ� ��ȯ
		return iter->second;
	}
    // �ƴ� ��� �ִϸ��̼��� �ε��ϰ� �ʿ� ����
    AnimationAsset* animation;
    //CSV ������ ���� �ִϸ��̼� ������ �ε�
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
    //CSV ���� ����
    std::wifstream file(filename);
    if (!file.is_open())
	{
        return false;
	}
    //wiftream �� wstringstram���� ��ȯ
    
    //���پ� �о����
    std::wstring line;
    while (std::getline(file, line))
	{
		//������ ,�� ����� ������ �о��
		std::wstringstream wss(line);
		std::wstring name;
		wss >> name;
		//�ִϸ��̼� �̸��̸� �ִϸ��̼� ������ �߰�
		if (name == L"Animation")
		{
			AnimationAsset::AnimationInfo info;
			wss >> info.name;
			//������ ������ �߰�
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

