#include "pch.h"
#include "SceneComponent.h"

SceneComponent::SceneComponent()
{
}

SceneComponent::~SceneComponent()
{
}

void SceneComponent::Init()
{
	transform = D2D1::Matrix3x2F::Identity();
	position = { 0,0 };
	rotation = 0;
	scale = { 1,1 };
}

void SceneComponent::Update()
{
	UpdateTransform();
}

void SceneComponent::Render()
{
}

void SceneComponent::Release()
{
}

//Æ®·»½ºÆûÀ» °è»êÇÏ¿© ¿ùµåÆ®·»½ºÆûÀ» ¾÷µ¥ÀÌÆ®
void SceneComponent::UpdateTransform()
{
	//¿ÀºêÁ§Æ®ÀÇ Æ®·»½ºÆûÀ» °è»ê
	transform = D2D1::Matrix3x2F::Translation(position.x,position.y) * D2D1::Matrix3x2F::Rotation(rotation) * D2D1::Matrix3x2F::Scale(scale.x,scale.y);
	//ºÎ¸ð°´Ã¼°¡ Á¸ÀçÇÑ´Ù¸é ºÎ¸ð°´Ã¼ÀÇ Æ®·»½ºÆûÀ» °öÇÏ¿© ¿ùµåÆ®·»½ºÆûÀ» °è»ê
	if (parent)
	{
		worldMatrix = transform*parent->worldMatrix;
	}
	else
	{
		worldMatrix = transform;
	}	
}
