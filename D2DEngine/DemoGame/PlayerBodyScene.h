#pragma once
#include "../D2DEngine/AnimationScene.h"
class PlayerBodyScene :public AnimationScene
{
	public:
	PlayerBodyScene();
	virtual ~PlayerBodyScene() = default;
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1RenderTarget* pRenderTarget);
};

