#include "AnimationAsset.h"
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

bool ResourceManager::CreateAnimationAssetFromFile(std::wstring wstrFilePath, AnimationAsset** Animation)
{
    if (mAnimationAssetMap.find(wstrFilePath) != mAnimationAssetMap.end()) {
        *Animation = mAnimationAssetMap[wstrFilePath];
        (*Animation)->AddRef();
        return true;
    }
    AnimationAsset* pTemp = new AnimationAsset;
    if (pTemp->LoadAnimation(wstrFilePath))
    {
        *Animation = pTemp;
        (*Animation)->AddRef();
    }
    else {
        delete pTemp;
        return false;
    }


    mAnimationAssetMap[wstrFilePath] = *Animation;
    return true;
}

void ResourceManager::ReleaseAnimationAsset(std::wstring wstrFilePath)
{
    std::map<std::wstring, AnimationAsset*>::iterator iter = mAnimationAssetMap.find(wstrFilePath);
    if (iter != mAnimationAssetMap.end())
    {
        AnimationAsset* Animation = mAnimationAssetMap[wstrFilePath];
        std::cout <<"RefCount: " << Animation->GetRefCount() << std::endl;
        if (Animation->Release() == 0)
        {
            mAnimationAssetMap.erase(iter);
        }
    }
}
