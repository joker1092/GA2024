#include "World.h"
#include "Scene.h"
#include "Camera.h"

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
	

		
	Scene::UpdateTrasnform();
	pD2DRender->m_CameraTransform=m_WorldTransform;
	D2D1InvertMatrix(&pD2DRender->m_CameraTransform);
	
	float x= m_WorldTransform._31+width/2;
	float y= m_WorldTransform._32+height/2;
	m_ViewBoundBox.m_Center = {x,y};
}

