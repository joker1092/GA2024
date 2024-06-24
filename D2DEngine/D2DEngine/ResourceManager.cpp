#include "ResourceManager.h"


ResourceManager::ResourceManager()
{
    ResourceManager::pInstance = this;
}

ResourceManager::ResourceManager(D2DRender* _pRender)
{
    pRender = _pRender;
    ResourceManager::pInstance = this;
}

ResourceManager::~ResourceManager()
{
}

ResourceManager* ResourceManager::pInstance = nullptr;

bool ResourceManager::CreateD2DBitmapFrmaFile(std::wstring wstrFilePath, ID2D1Bitmap** bitmap)
{
    if (mBitmapMap.find(wstrFilePath) != mBitmapMap.end()) {
        *bitmap = mBitmapMap[wstrFilePath];
        (*bitmap)->AddRef();
        return true;
    }

    HRESULT hr;
    hr = pRender->D2DBitmapFromFile(wstrFilePath.c_str(), bitmap);
    if (FAILED(hr))
    {
        return false;
    }

    mBitmapMap[wstrFilePath] = *bitmap;

    return true;
}

void ResourceManager::ReleaseD2DBitmap(std::wstring wstrFilePath)
{
    std::map<std::wstring, ID2D1Bitmap*>::iterator iter = mBitmapMap.find(wstrFilePath);
    if (iter!= mBitmapMap.end())
    {
        ID2D1Bitmap* bitmap = mBitmapMap[wstrFilePath];
        if (bitmap->Release()==0)
        {
            mBitmapMap.erase(iter);
        }
    }
}
