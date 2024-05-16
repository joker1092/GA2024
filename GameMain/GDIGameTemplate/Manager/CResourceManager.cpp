#include "CResourceManager.h"
#include "CPathManager.h"


CPathManager path;

CResourceManager* CResourceManager::instance = nullptr;

CResourceManager::CResourceManager() {
	//path ��� �ʱ�ȭ 
	path.Init();
}

CResourceManager::~CResourceManager() {
	//�Ҹ��ڿ��� map ��ȸ�ϸ� ��ü ���ҽ� ����
	std::map<std::wstring, Gdiplus::Bitmap*>::iterator iter = m_mapBitmap.begin();
	for (; iter != m_mapBitmap.end(); ++iter) {
		if (iter->second != nullptr) {
			delete iter->second;
		}
		
	}
	
	std::map<std::wstring, AnimationResource*>::iterator iterAnimation = m_mapAnimation.begin();
	for (; iter != m_mapBitmap.end(); ++iter) {
		if (iter->second != nullptr) {
			delete iter->second;
		}
	}
	m_mapBitmap.clear();
	m_mapAnimation.clear();
}

Gdiplus::Bitmap* CResourceManager::LoadBitmapResouce(const std::wstring& _strkey, const std::wstring& _path)
{
	//Ű������ map���� ã��
	Gdiplus::Bitmap* pBitmap = FindBitmapResouce(_strkey);
	//������ ��ȯ
	if (pBitmap != nullptr)
	{
		return pBitmap;
	}
	//pathmanager�� ����� ���̱�
	//std::wstring strFilePath = path.GetContentPath(); //�� ������ ��ġ��!!
	//strFilePath += _path;
	//bitmap �ε�
	pBitmap = Gdiplus::Bitmap::FromFile(_path.c_str());
	//map�� ���� �ϰ�
	m_mapBitmap.insert(make_pair(_strkey, pBitmap));
	//bitmap* ����
	return pBitmap;
}

Gdiplus::Bitmap* CResourceManager::FindBitmapResouce(const std::wstring& _strkey)
{
	//map�� ���ͷ����͸� ��� key������ ã��
	std::map<std::wstring, Gdiplus::Bitmap*>::iterator iter = m_mapBitmap.find(_strkey);
	//iterator ����� ���� ���� ��� --> map�� ���빰�� ���°�� nullptr ��ȯ
	if (iter == m_mapBitmap.end())
	{
		return nullptr;
	}
	//�ִ� ��� <first,second> -> <key,���빰>�̹Ƿ� ���빰�� ��ȯ
	return iter->second;
}

AnimationResource* CResourceManager::LoadAnimationResouce(const std::wstring& _strkey, const std::wstring& _path)
{
	//Ű������ map���� ã��
	AnimationResource* pAnimation = FindAnimationResouce(_strkey);
	//������ ��ȯ
	if (pAnimation != nullptr)
	{
		return pAnimation;
	}
	//pathmanager�� ����� ���̱�
	//std::wstring strFilePath = path.GetContentPath(); 
	//strFilePath += _path;
	//bitmap �ε�
	pAnimation = new AnimationResource();
	pAnimation->LoadAnimImage(_path.c_str());
	//map�� ���� �ϰ�
	m_mapAnimation.insert(make_pair(_strkey, pAnimation));
	//bitmap* ����
	return pAnimation;
}

AnimationResource* CResourceManager::FindAnimationResouce(const std::wstring& _strkey)
{
	//map�� ���ͷ����͸� ��� key������ ã��
	std::map<std::wstring, AnimationResource*>::iterator iter = m_mapAnimation.find(_strkey);
	//iterator ����� ���� ���� ��� --> map�� ���빰�� ���°�� nullptr ��ȯ
	if (iter == m_mapAnimation.end())
	{
		return nullptr;
	}
	//�ִ� ��� <first,second> -> <key,���빰>�̹Ƿ� ���빰�� ��ȯ
	return iter->second;
}

void CResourceManager::setAnimationMotion(const std::wstring& _strkey, const std::wstring& _path, bool IsLoop)
{
	AnimationResource* pAnimation = FindAnimationResouce(_strkey);
	if (pAnimation==nullptr)
	{
		return;
	}

	/*std::wstring strFilePath = path.GetContentPath();
	strFilePath += _path;*/
	pAnimation->LoadAnimMotion(_path.c_str(), IsLoop);
}


CResourceManager* CResourceManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new CResourceManager();
	}
	return instance;
}

void CResourceManager::DestroyInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}
