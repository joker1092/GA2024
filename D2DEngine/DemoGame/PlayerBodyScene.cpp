#include "framework.h"
#include "PlayerBodyScene.h"

PlayerBodyScene::PlayerBodyScene()
{
	
}

void PlayerBodyScene::Update(float deltaTime)
{
	AnimationScene::Update(deltaTime);
}

void PlayerBodyScene::Render(ID2D1RenderTarget* pRenderTarget)
{
	AnimationScene::Render(pRenderTarget);
}
