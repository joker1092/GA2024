#pragma once

//��ü ���ҽ� ���� Ŭ����
class D2DRender;
class AnimationAsset;
class ResouceManger
{
static ResouceManger* m_pInstance;

//��Ʈ�� ������ ��� ��
std::map<std::wstring, ID2D1Bitmap*> m_BitmapMap;
//�ִϸ��̼� ������ ��� ��
std::map<std::wstring, AnimationAsset*> m_AnimationMap;
//todo: �߰����� ���ҽ��� ���� ���� �����Ѵ�.

public:
		ResouceManger();
		~ResouceManger();
		static ResouceManger* GetInstance();
		static void ReleaseInstance();
		//file�κ��� ��Ʈ�� ������ �ε��Ͽ� �ʿ� �����ϰ� �ش� ��Ʈ���� �ּҸ� ��ȯ�ϴ� �Լ�
		ID2D1Bitmap* LoadBitmapFromFile(const std::wstring& _fileName);
		//file�κ��� �ִϸ��̼� ������ �ε��Ͽ� �ʿ� �����ϰ� �ش� �ִϸ��̼��� �ּҸ� ��ȯ�ϴ� �Լ�
		AnimationAsset* LoadAnimationFromFile(const std::wstring& _fileName);
		bool AnimationFromCSV(const std::wstring& filename, AnimationAsset**);

};

