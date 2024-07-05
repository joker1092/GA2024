#pragma once

//게임의 보여주는 하나의 월드
//오브젝트들이 존재하고 업데이트, 렌더링이 이루어지는 곳
class Object;
class World
{
	//월드를 구분할수 있는 고유번호
	static int m_worldID;
	std::list<Object*> m_objects; //월드에 존재하는 모든 오브젝트들
	std::list<Object*> m_renderList; //오브젝트중 렌더링이 필요한 오브젝트들
	//월드의 크기
	int m_width;
	int m_height;
	//월드에서 화면에 비춰질 메인 카메라 오브젝트
	Object* m_mainCamera;
public:
	World();
	~World();
	void Init();
	void Update();
	void Render();
	void Release();
	//월드에서 오브젝트를 생성하여 리스트에 등록후 오브젝트 타입 반환

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

