#pragma once
//������Ʈ�� ���� �� �ִ� ������Ʈ�� �θ�Ŭ����
#include "Object.h"
class Object;
class Component
{
	//�����ִ� ������Ʈ�� �ּ�
	Object* object;
public:
	Component();
	~Component();
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();
};

