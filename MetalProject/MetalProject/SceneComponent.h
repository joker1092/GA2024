#pragma once
#include "Component.h"

//������Ʈ�� ��ġ, ȸ��, �������� ����ϴ� ������Ʈ
class SceneComponent :   public Component
{
	//�θ�ü�� SceneComponent�� �ּ�
	SceneComponent* parent=nullptr;
	//������Ʈ ���� Ʈ������
	D2D1_MATRIX_3X2_F worldMatrix;
	//������Ʈ�� ��ġ
	D2D1_POINT_2F position;
	//������Ʈ�� ȸ��
	float rotation;
	//������Ʈ�� ������
	D2D1_POINT_2F scale;
	//������Ʈ�� Ʈ������
	D2D1_MATRIX_3X2_F transform;
public:
	SceneComponent();
	~SceneComponent();
	void Init();
	void Update();
	void Render();
	void Release();
	//�θ�ü�� SceneComponent�� �ּҸ� ����
	void SetParent(SceneComponent* _parent) { parent = _parent; }
	void UpdateTransform();
};

