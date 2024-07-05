#pragma once
//오브젝트에 붙일 수 있는 컴포넌트의 부모클래스
#include "Object.h"
class Object;
class Component
{
	//속해있는 오브젝트의 주소
	Object* object;
public:
	Component();
	~Component();
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();
};

