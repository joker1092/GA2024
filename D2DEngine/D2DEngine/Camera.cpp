#include "World.h"
#include "Scene.h"
#include "Camera.h"

//todo:
//카메라가 월드의 끝에 도달하면 월드의 끝에서 더이상 이동하지 못하게 한다.
//그렇다면 카메라가 월드의 끝에 도달하면 어떻게 처리해야 할까?
//카메라가 월드의 끝에 도달하면 카메라의 위치를 월드의 끝으로 설정하면 된다.


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

	//여기서 카메라의 위치와 월드의 끝값을 비교
	//카메라의 위치가 월드의 끝값보다 크면 카메라의 위치를 월드의 끝값으로 설정
	//월드의 끝값은 World클래스의 m_fWorldMaxX, m_fWorldMaxY에 저장되어 있다.
	//카메라의 위치는 m_RelativeLocation에 저장되어 있다.
	//월드의 끝값을 불러오자
	float WorldMaxX = pWorld->m_fWorldMaxX;
	float WorldMaxY = pWorld->m_fWorldMaxY;
	//min값은 0으로 설정
	float WorldMinZero = 0;

	//카메라의 위치를 불러오자
	float CameraX = m_RelativeLocation.x;
	float CameraY = m_RelativeLocation.y;
	
	//카메라의 위치가 월드의 끝값보다 크면 카메라의 위치를 월드의 끝값으로 설정
	//min,max 값을 모두 비교
	CameraX = min(CameraX, WorldMaxX);
	CameraX = max(CameraX, WorldMinZero);
	CameraY = min(CameraY, WorldMaxY);
	CameraY = max(CameraY, WorldMinZero);
	
	m_RelativeLocation.x = CameraX;
	m_RelativeLocation.y = CameraY;
	

		
	Scene::UpdateTrasnform();
	pD2DRender->m_CameraTransform=m_WorldTransform;
	D2D1InvertMatrix(&pD2DRender->m_CameraTransform);
	
	float x= m_WorldTransform._31+width/2;
	float y= m_WorldTransform._32+height/2;
	m_ViewBoundBox.m_Center = {x,y};
}

