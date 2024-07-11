#pragma once
#include "GameObject.h"
#include "AABB.h"
#include "Camera.h"

// 게임의 세계를 나타내는 클래스
// GameObect타입으로 생성된 객체들을 관리하여 Update, Render를 호출한다.
class World
{
public:
	World();
	virtual ~World();
	int objectCount = 0;
	int renderCount = 0;
	std::list<GameObject*> m_GameObjects;
	std::vector< GameObject*> m_RenderQueue;
	AABB* m_pCullingBound = nullptr;
	AABB m_CullingBoundDefault;
	
public:
	void Update(float deltaTime);
	void Render(ID2D1RenderTarget* pRenderTarget, ID2D1SolidColorBrush* brush);
	void Clear();
	void SetCullingBound(AABB* pBound) { m_pCullingBound = pBound; }
	Camera* m_pCamera = nullptr;
	// 템플릿 함수로 GameObject를 생성한다.

	Camera* GetCamera() { return m_pCamera; }



	template<typename T>
	T* CreateGameObject()
	{
		bool bIsBase = std::is_base_of<GameObject, T>::value;
		assert(bIsBase == true);	// GameObject를 상속받은 클래스만 생성할 수 있다.
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

