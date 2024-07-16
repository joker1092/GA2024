#pragma once
#include "../D2DEngine/Collider.h"
class PlayerNotify : public IColliderNotify
{
	// IColliderNotify을(를) 통해 상속됨
	void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
};

