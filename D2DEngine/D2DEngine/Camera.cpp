#include "World.h"
#include "Scene.h"
#include "Camera.h"
#include "MathHelper.h"

//todo:
//ī�޶� ������ ���� �����ϸ� ������ ������ ���̻� �̵����� ���ϰ� �Ѵ�.
//�׷��ٸ� ī�޶� ������ ���� �����ϸ� ��� ó���ؾ� �ұ�?
//ī�޶� ������ ���� �����ϸ� ī�޶��� ��ġ�� ������ ������ �����ϸ� �ȴ�.


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
		//ī�޶� Ÿ���� ����ٴϰ� �Ѵ�.
		float x = pTargetScene->m_RelativeLocation.x - width / 2;
		float y = pTargetScene->m_RelativeLocation.y - height / 2;
		m_RelativeLocation.x = x;
		m_RelativeLocation.y = y;
	}
	//std::cout << m_RelativeLocation.x << "," << m_RelativeLocation.y << std::endl;

	//���⼭ ī�޶��� ��ġ�� ������ ������ ��
	//ī�޶��� ��ġ�� ������ �������� ũ�� ī�޶��� ��ġ�� ������ �������� ����
	//������ ������ WorldŬ������ m_fWorldMaxX, m_fWorldMaxY�� ����Ǿ� �ִ�.
	//ī�޶��� ��ġ�� m_RelativeLocation�� ����Ǿ� �ִ�.
	//������ ������ �ҷ�����
	float WorldMaxX = pWorld->m_fWorldMaxX;
	float WorldMaxY = pWorld->m_fWorldMaxY;
	//min���� 0���� ����
	float WorldMinZero = 0;

	//ī�޶��� ��ġ�� �ҷ�����
	float CameraX = m_RelativeLocation.x;
	float CameraY = m_RelativeLocation.y;
	
	//ī�޶��� ��ġ�� ������ �������� ũ�� ī�޶��� ��ġ�� ������ �������� ����
	//min,max ���� ��� ��
	CameraX = min(CameraX, WorldMaxX);
	CameraX = max(CameraX, WorldMinZero);
	CameraY = min(CameraY, WorldMaxY);
	CameraY = max(CameraY, WorldMinZero);
	
	m_RelativeLocation.x = CameraX;
	m_RelativeLocation.y = CameraY;
	
	//���� ī�޶� �����Ǿ� �ִٸ� ���� ī�޶�� ����
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
		// ������Ʈ�� ��ġ�� �����ɴϴ�.
		D2D1_VECTOR_2F objectPosition = pScene->GetWorldLocation();

		// ī�޶� ������ ������� �ϴ��� Ȯ���մϴ�.
		if (!ContainsVector(objectPosition))
		{
			// ������Ʈ�� ī�޶� ���� ���� �ǵ����ϴ�.
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

