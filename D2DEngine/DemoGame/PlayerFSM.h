#pragma once
#include "../D2DEngine/D2DRender.h"
#include "../D2DEngine/FSM.h"
class PlayerFSM :  public FSM
{
	public:
	PlayerFSM();
	~PlayerFSM();
	void Initialize();
	void Update(float deltaTime);
	void Render(ID2D1RenderTarget* pRenderTarget);
	void Release();
};

