#include "Camera.h"

Camera::Camera()
{
	float width = 1920;
	float height = 1280;

	m_ViewBoundBox.SetExtent(width / 2, height / 2);

}

Camera::~Camera()
{
}

void Camera::Update(float deltaTime)
{
	Scene::UpdateTrasform();	
	m_ViewBoundBox.m_Center = GetWorldLocation();
}

