#pragma once
#include "../D2DEngine/AnimationScene.h"
class PlayerWorkScene :public AnimationScene
{
	public:
	PlayerWorkScene();
	virtual ~PlayerWorkScene() = default;
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1RenderTarget* pRenderTarget);
};

