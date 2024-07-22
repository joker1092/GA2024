#include "framework.h"
#include "PlayerWorkScene.h"

PlayerWorkScene::PlayerWorkScene()
{

}

void PlayerWorkScene::Update(float deltaTime)
{
	AnimationScene::Update(deltaTime);
}

void PlayerWorkScene::Render(ID2D1RenderTarget* pRenderTarget)
{
	AnimationScene::Render(pRenderTarget);
}
