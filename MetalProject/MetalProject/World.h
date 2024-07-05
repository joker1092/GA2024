#pragma once

//������ �����ִ� �ϳ��� ����
//������Ʈ���� �����ϰ� ������Ʈ, �������� �̷������ ��
class Object;
class World
{
	//���带 �����Ҽ� �ִ� ������ȣ
	static int m_worldID;
	std::list<Object*> m_objects; //���忡 �����ϴ� ��� ������Ʈ��
	std::list<Object*> m_renderList; //������Ʈ�� �������� �ʿ��� ������Ʈ��
	//������ ũ��
	int m_width;
	int m_height;
	//���忡�� ȭ�鿡 ������ ���� ī�޶� ������Ʈ
	Object* m_mainCamera;
public:
	World();
	~World();
	void Init();
	void Update();
	void Render();
	void Release();
	//���忡�� ������Ʈ�� �����Ͽ� ����Ʈ�� ����� ������Ʈ Ÿ�� ��ȯ

	template<typename T>
	T* CreateObject()
	{
		static_assert(std::is_base_of<Object, T>::value, "T must inherit from Object");
		T* object = new T();
		object->m_world = this;
		object->Init();
		m_objects.push_back(object);
		return object;
	}
};

