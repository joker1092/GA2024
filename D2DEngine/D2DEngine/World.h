#pragma once
#include "GameObject.h"
#include "AABB.h"

// ������ ���踦 ��Ÿ���� Ŭ����
// GameObectŸ������ ������ ��ü���� �����Ͽ� Update, Render�� ȣ���Ѵ�.
class World
{
public:
	World();
	virtual ~World();

	std::list<GameObject*> m_GameObjects;
	AABB* m_pCullingBound = nullptr;
	AABB m_CullingBoundDefault;
public:
	void Update(float deltaTime);
	void Render(ID2D1RenderTarget* pRenderTarget);
	void Clear();
	void SetCullingBound(AABB* pBound) { m_pCullingBound = pBound; }
	// ���ø� �Լ��� GameObject�� �����Ѵ�.
	template<typename T>
	T* CreateGameObject()
	{
		bool bIsBase = std::is_base_of<GameObject, T>::value;
		assert(bIsBase == true);	// GameObject�� ��ӹ��� Ŭ������ ������ �� �ִ�.
		T* newObject = new T();
		newObject->SetOwner(this);
		m_GameObjects.push_back(newObject);
		return newObject;
	}

	std::list<GameObject*>::iterator findGameobject(GameObject* pGameObject) {
		std::list<GameObject*>::iterator iter;
		for (auto iter = m_GameObjects.begin(); iter != m_GameObjects.end(); iter++)
		{
			if (*iter == pGameObject) {
				return iter;
			}
		}
	}


	bool DeleteGameObject(GameObject* pGameObject) {
		std::list<GameObject*>::iterator iter;
		iter = findGameobject(pGameObject);
		if (*iter==nullptr)
		{
			return false;
		}
		(*iter)->~GameObject();
		m_GameObjects.erase(iter);
		return true;
	}
};

