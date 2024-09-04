#include "World.h"
#include "Scene.h"
#include "Camera.h"
#include "MathHelper.h"

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
	
	//고정 카메라가 설정되어 있다면 고정 카메라로 설정
	if (isFixed)
	{
		m_RelativeLocation = m_FixedLocation;
	}

		
	Scene::UpdateTrasnform();
	pD2DRender->m_CameraTransform=m_WorldTransform;
	D2D1InvertMatrix(&pD2DRender->m_CameraTransform);
	
	float x= m_WorldTransform._31+width/2;
	float y= m_WorldTransform._32+height/2;
	m_ViewBoundBox.m_Center = {x,y};
}

void Camera::ObjectClampToCamera(Scene* pScene)
{
	
	if (pScene != nullptr)
	{
		// 오브젝트의 위치를 가져옵니다.
		D2D1_VECTOR_2F objectPosition = pScene->GetWorldLocation();

		// 카메라 영역을 벗어나려고 하는지 확인합니다.
		if (!ContainsVector(objectPosition))
		{
			// 오브젝트를 카메라 영역 내로 되돌립니다.
			D2D1_VECTOR_2F clampedPosition = VectorClamp(objectPosition);
			pScene->SetRelativeLocation(clampedPosition);
		}
	}
}

bool Camera::ContainsVector(D2D1_VECTOR_2F v)
{
	D2D1_RECT_F rect = { m_ViewBoundBox.GetMinX(),m_ViewBoundBox.GetMinY(),m_ViewBoundBox.GetMaxX(),m_ViewBoundBox.GetMaxY()};
	
	if (v.x >= rect.left && v.x <= rect.right && v.y >= rect.top && v.y <= rect.bottom)
	{
		return true;
	}
	return false;
}

D2D1_VECTOR_2F Camera::VectorClamp(D2D1_VECTOR_2F v) {
	D2D1_VECTOR_2F clampedVector = { 0,0 };
	clampedVector.x = min(v.x, m_ViewBoundBox.GetMaxX());
	clampedVector.x = max(clampedVector.x, m_ViewBoundBox.GetMinX());
	clampedVector.y = min(v.y, m_ViewBoundBox.GetMaxY());
	clampedVector.y = max(clampedVector.y, m_ViewBoundBox.GetMinY());
	return clampedVector;
}

