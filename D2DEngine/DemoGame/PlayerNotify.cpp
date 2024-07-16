#include "PlayerNotify.h"

void PlayerNotify::OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	std::cout<< "PlayerNotify::OnBlock" << std::endl;
	std::cout<< "pOwnedComponent: " << pOwnedComponent << std::endl;
	std::cout<< "pOtherComponent: " << pOtherComponent << std::endl;
}

void PlayerNotify::OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	std::cout << "PlayerNotify::OnBeginOverlap" << std::endl;
	std::cout << "pOwnedComponent: " << pOwnedComponent << std::endl;
	std::cout << "pOtherComponent: " << pOtherComponent << std::endl;
}

void PlayerNotify::OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	std::cout << "PlayerNotify::OnEndOverlap" << std::endl;
	std::cout << "pOwnedComponent: " << pOwnedComponent << std::endl;
	std::cout << "pOtherComponent: " << pOtherComponent << std::endl;
}
