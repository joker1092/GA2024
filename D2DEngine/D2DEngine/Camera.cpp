#include "Camera.h"

Camera::Camera()
{
	float width = 640;
	float height = 480;

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
