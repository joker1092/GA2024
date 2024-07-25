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
	std::list<GameObject*> m_GameObjects; // 게임 오브젝트들을 담는 리스트
	std::list<GameObject*> m_DeleteObjects; //삭제할 오브젝트를 담는 리스트
	std::vector< GameObject*> m_RenderQueue; // 렌더링 순서를 정하기 위한 큐
	AABB* m_pCullingBound = nullptr;
	AABB m_CullingBoundDefault;

	float m_fWorldMaxX = 5000.0f; // 월드의 최대 x좌표 0~5000
	float m_fWorldMaxY = 5000.0f; // 월드의 최대 y좌표 0~5000
	
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

	// 각 오브젝트 상황에서 삭제할 오브젝트를 배열에 넣어놓고 한번에 삭제한다.
	// 이유는 Update에서 삭제하면 다음 오브젝트가 삭제된 오브젝트를 참조할 수 있기 때문이다.
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

