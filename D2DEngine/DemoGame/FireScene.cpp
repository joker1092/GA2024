#include "FireScene.h"
#include "Player.h"
FireScene::FireScene()
{
}

void FireScene::Update(float deltaTime)
{
	Player* player = dynamic_cast<Player*>(m_pOwner);
	if (player->flip)
	{
		m_RelativeLocation.x =-30;
	}
	else {
		m_RelativeLocation.x = 30;
	}
	Scene::Update(deltaTime);
}

void FireScene::Render(ID2D1RenderTarget* pRenderTarget)
{
}
