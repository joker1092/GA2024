#pragma once
#include "../D2DEngine/Scene.h"
class FireScene : public Scene
{
	public:
	FireScene();
	virtual ~FireScene() = default;
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1RenderTarget* pRenderTarget);
};

