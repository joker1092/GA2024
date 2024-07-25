#pragma once
#include "GameObject.h"
#include "AABB.h"
#include "Camera.h"

// ������ ���踦 ��Ÿ���� Ŭ����
// GameObectŸ������ ������ ��ü���� �����Ͽ� Update, Render�� ȣ���Ѵ�.
class World
{
public:
	World();
	virtual ~World();
	int objectCount = 0;
	int renderCount = 0;
	std::list<GameObject*> m_GameObjects; // ���� ������Ʈ���� ��� ����Ʈ
	std::list<GameObject*> m_DeleteObjects; //������ ������Ʈ�� ��� ����Ʈ
	std::vector< GameObject*> m_RenderQueue; // ������ ������ ���ϱ� ���� ť
	AABB* m_pCullingBound = nullptr;
	AABB m_CullingBoundDefault;

	float m_fWorldMaxX = 5000.0f; // ������ �ִ� x��ǥ 0~5000
	float m_fWorldMaxY = 5000.0f; // ������ �ִ� y��ǥ 0~5000
	
public:
	void Update(float deltaTime);
	void Render(ID2D1RenderTarget* pRenderTarget, ID2D1SolidColorBrush* brush);
	void Clear();
	void SetCullingBound(AABB* pBound) { m_pCullingBound = pBound; }
	Camera* m_pCamera = nullptr;
	// ���ø� �Լ��� GameObject�� �����Ѵ�.

	Camera* GetCamera() { return m_pCamera; }



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
		return iter;
	}

	template<typename T>
	T* FindPointGameObject()
	{
		for (auto pObject : m_GameObjects)
		{
			T* pT = dynamic_cast<T*>(pObject);
			if (pT != nullptr)
			{
				return pT;
			}
		}
		return nullptr;
	}

	// �� ������Ʈ ��Ȳ���� ������ ������Ʈ�� �迭�� �־���� �ѹ��� �����Ѵ�.
	// ������ Update���� �����ϸ� ���� ������Ʈ�� ������ ������Ʈ�� ������ �� �ֱ� �����̴�.
	void DeleteObject(GameObject* pGameObject) {
		m_DeleteObjects.push_back(pGameObject);
	}


	bool DeleteGameObject(GameObject* pGameObject) {
		std::list<GameObject*>::iterator iter;
		iter = findGameobject(pGameObject);
		if (iter == m_GameObjects.end())
		{
			return false;
		}
		(*iter)->~GameObject();
		m_GameObjects.erase(iter);
		return true;
	}
};

