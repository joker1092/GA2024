#pragma once

//월드에 존재할 수 있는 모든 오브젝트의 부모클래스
class World;
class Component;
class Object
{
	//속해있는 월드에 대한 주소
	World* m_world;
	//가지고 있는 컴포넌트들
	std::list<Component*> m_components;
	//component 중 중심이 되는 transform 컴포넌트
	Component* m_transform;
public:
	Object();
	~Object();
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	//컴포넌트를 생성하여 리스트에 등록후 컴포넌트 타입 반환
	template<typename T>
	T* AddComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
		T* component = new T();
		component->object = this;
		component->Init();
		m_components.push_back(component);
		return component;
	}
};

