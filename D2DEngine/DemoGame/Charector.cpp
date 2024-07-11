#include "framework.h"
#include "../D2DEngine/WinGameApp.h"
#include "../D2DEngine/Scene.h"
#include "../D2DEngine/BitmapScene.h"
#include "../D2DEngine/AnimationScene.h"
#include "../D2DEngine/Camera.h"
#include "../D2DEngine/FSM.h"
#include "../D2DEngine/FSMState.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/InputSystem.h"
#include "Charector.h"

Charector::Charector()
{

}

void Charector::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
}
