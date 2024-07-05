#pragma once

//���忡 ������ �� �ִ� ��� ������Ʈ�� �θ�Ŭ����
class World;
class Component;
class Object
{
	//�����ִ� ���忡 ���� �ּ�
	World* m_world;
	//������ �ִ� ������Ʈ��
	std::list<Component*> m_components;
	//component �� �߽��� �Ǵ� transform ������Ʈ
	Component* m_transform;
public:
	Object();
	~Object();
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	//������Ʈ�� �����Ͽ� ����Ʈ�� ����� ������Ʈ Ÿ�� ��ȯ
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

