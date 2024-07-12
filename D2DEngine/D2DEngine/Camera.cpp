#include "Scene.h"
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
	float width = 1920;
	float height = 1280;
	//std::cout << pTargetScene << std::endl;
	if (pTargetScene!=nullptr)
	{
		D2D1_VECTOR_2F s = pTargetScene->GetWorldLocation();
		//std::cout << s.x << "," << s.y << std::endl;
		//카메라가 타겟을 따라다니게 한다.
		float x = pTargetScene->m_RelativeLocation.x - width / 2;
		float y = pTargetScene->m_RelativeLocation.y - height / 2;
		m_RelativeLocation.x = x;
		m_RelativeLocation.y = y;
	}
	//std::cout << m_RelativeLocation.x << "," << m_RelativeLocation.y << std::endl;
	
	Scene::UpdateTrasnform();
	pD2DRender->m_CameraTransform=m_WorldTransform;
	D2D1InvertMatrix(&pD2DRender->m_CameraTransform);
	
	float x= m_WorldTransform._31+width/2;
	float y= m_WorldTransform._32+height/2;
	m_ViewBoundBox.m_Center = {x,y};
}

