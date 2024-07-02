#pragma once
#include "Scene.h"
#include "Component.h"
#include "D2DRender.h"
#include "ResourceManager.h"

class D2DRender;

class BitmapScene : public Scene, public Component
{
public:
	BitmapScene();
	virtual ~BitmapScene();

	std::wstring wsBitmapFilePath;
	ID2D1Bitmap* pBitmap = nullptr;
	ResourceManager* pRM;

	bool LoadD2DBitmap(const std::wstring strFilePath, D2DRender* _pRender);
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1RenderTarget* pRenderTarget);
	virtual D2D1_VECTOR_2F GetExtent() { return D2D1::Vector2F((pBitmap->GetSize().width)/2, (pBitmap->GetSize().height)/2); }
};

