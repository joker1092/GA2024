#pragma once
#include "../stdafx.h"
#include "../GameLogic/Animation.h"
class CResourceManager
{
	//Todo:
	//���� Gdiplus::Bitmap* �� ���� map �� ���������� animation�� sound �׿� �ʿ�� �߰� ���� �ʿ�
private:
	static CResourceManager* instance;
	//bitmap* ���� �� <key ��, ���빰> �� ��Ƽ� ���� ���� 
	std::map<std::wstring, Gdiplus::Bitmap*> m_mapBitmap;
	std::map<std::wstring, AnimationResource*> m_mapAnimation;

public:
	CResourceManager();
	~CResourceManager();
	static CResourceManager* GetInstance();
	static void DestroyInstance();
	//ã�� �ҷ����� Load�� �� map�� ����ִ����� �Ǵ� �Ͽ� ������ �ִ� ���빰�� ������ bitmap*�� ������ �ҷ����� ���
	Gdiplus::Bitmap* LoadBitmapResouce(const std::wstring& _strkey, const std::wstring& _path);
	Gdiplus::Bitmap* FindBitmapResouce(const std::wstring& _strkey);
	AnimationResource* LoadAnimationResouce(const std::wstring& _strkey, const std::wstring& _path);
	AnimationResource* FindAnimationResouce(const std::wstring& _strkey);
	void setAnimationMotion(const std::wstring& _strkey, const std::wstring& _path, bool IsLoop = true);
};

