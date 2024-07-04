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
	Scene::UpdateTrasnform();
	pD2DRender->m_CameraTransform=m_WorldTransform;
	D2D1InvertMatrix(&pD2DRender->m_CameraTransform);
	float width = 1920;
	float height = 1280;
	float x= m_WorldTransform._31+width/2;
	float y= m_WorldTransform._32+height/2;
	m_ViewBoundBox.m_Center = {x,y};
}

