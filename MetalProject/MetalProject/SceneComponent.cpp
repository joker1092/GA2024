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

//Ʈ�������� ����Ͽ� ����Ʈ�������� ������Ʈ
void SceneComponent::UpdateTransform()
{
	//������Ʈ�� Ʈ�������� ���
	transform = D2D1::Matrix3x2F::Translation(position.x,position.y) * D2D1::Matrix3x2F::Rotation(rotation) * D2D1::Matrix3x2F::Scale(scale.x,scale.y);
	//�θ�ü�� �����Ѵٸ� �θ�ü�� Ʈ�������� ���Ͽ� ����Ʈ�������� ���
	if (parent)
	{
		worldMatrix = transform*parent->worldMatrix;
	}
	else
	{
		worldMatrix = transform;
	}	
}
