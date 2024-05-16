#include "CResourceManager.h"
#include "CPathManager.h"


CPathManager path;

CResourceManager* CResourceManager::instance = nullptr;

CResourceManager::CResourceManager() {
	//path 경로 초기화 
	path.Init();
}

CResourceManager::~CResourceManager() {
	//소멸자에서 map 순회하며 전체 리소스 해제
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
	//키값으로 map에서 찾기
	Gdiplus::Bitmap* pBitmap = FindBitmapResouce(_strkey);
	//있으면 반환
	if (pBitmap != nullptr)
	{
		return pBitmap;
	}
	//pathmanager로 상대경로 붙이기
	//std::wstring strFilePath = path.GetContentPath(); //요 언저리 고치기!!
	//strFilePath += _path;
	//bitmap 로드
	pBitmap = Gdiplus::Bitmap::FromFile(_path.c_str());
	//map에 저장 하고
	m_mapBitmap.insert(make_pair(_strkey, pBitmap));
	//bitmap* 전달
	return pBitmap;
}

Gdiplus::Bitmap* CResourceManager::FindBitmapResouce(const std::wstring& _strkey)
{
	//map의 이터레이터를 사용 key값으로 찾음
	std::map<std::wstring, Gdiplus::Bitmap*>::iterator iter = m_mapBitmap.find(_strkey);
	//iterator 종료시 까지 없는 경우 --> map에 내용물이 없는경우 nullptr 반환
	if (iter == m_mapBitmap.end())
	{
		return nullptr;
	}
	//있는 경우 <first,second> -> <key,내용물>이므로 내용물을 반환
	return iter->second;
}

AnimationResource* CResourceManager::LoadAnimationResouce(const std::wstring& _strkey, const std::wstring& _path)
{
	//키값으로 map에서 찾기
	AnimationResource* pAnimation = FindAnimationResouce(_strkey);
	//있으면 반환
	if (pAnimation != nullptr)
	{
		return pAnimation;
	}
	//pathmanager로 상대경로 붙이기
	//std::wstring strFilePath = path.GetContentPath(); 
	//strFilePath += _path;
	//bitmap 로드
	pAnimation = new AnimationResource();
	pAnimation->LoadAnimImage(_path.c_str());
	//map에 저장 하고
	m_mapAnimation.insert(make_pair(_strkey, pAnimation));
	//bitmap* 전달
	return pAnimation;
}

AnimationResource* CResourceManager::FindAnimationResouce(const std::wstring& _strkey)
{
	//map의 이터레이터를 사용 key값으로 찾음
	std::map<std::wstring, AnimationResource*>::iterator iter = m_mapAnimation.find(_strkey);
	//iterator 종료시 까지 없는 경우 --> map에 내용물이 없는경우 nullptr 반환
	if (iter == m_mapAnimation.end())
	{
		return nullptr;
	}
	//있는 경우 <first,second> -> <key,내용물>이므로 내용물을 반환
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
