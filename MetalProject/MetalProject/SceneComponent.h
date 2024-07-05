#pragma once
#include "Component.h"

//오브젝트의 위치, 회전, 스케일을 담당하는 컴포넌트
class SceneComponent :   public Component
{
	//부모객체의 SceneComponent의 주소
	SceneComponent* parent=nullptr;
	//오브젝트 월드 트렌스폼
	D2D1_MATRIX_3X2_F worldMatrix;
	//오브젝트의 위치
	D2D1_POINT_2F position;
	//오브젝트의 회전
	float rotation;
	//오브젝트의 스케일
	D2D1_POINT_2F scale;
	//오브젝트의 트렌스폼
	D2D1_MATRIX_3X2_F transform;
public:
	SceneComponent();
	~SceneComponent();
	void Init();
	void Update();
	void Render();
	void Release();
	//부모객체의 SceneComponent의 주소를 설정
	void SetParent(SceneComponent* _parent) { parent = _parent; }
	void UpdateTransform();
};

