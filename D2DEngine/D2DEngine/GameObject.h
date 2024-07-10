#pragma once
#include "AABB.h"



class Component;
class Scene;
class World;
class GameObject{
public:
	GameObject();
	virtual ~GameObject();
	enum ZOrder
	{
		DISABELED,
		BACKGROUND,
		OBJECT,
		ENEMY,
		PLAYER,
		EFFECT,
		UI,
	};
	std::vector<Component*> m_OwnedComponents;	// 소유한 컴포넌트들
	Scene* m_pRootScene = nullptr;				// 컴포넌트 중에 어느게 루트인지 설정
	World* m_pOwner = nullptr;					// 이 게임 오브젝트가 속한 월드
	AABB m_BoundBox;								// 바운딩 박스
	ZOrder m_ZOrder = ZOrder::DISABELED;			// ZOrder
	void Update(float deltaTime);
	void Render(ID2D1RenderTarget* pRenderTarget);
	void SetRootScene(Scene* pRootComponent) { m_pRootScene = pRootComponent; }
	const AABB& GetBoundBox() const { return m_BoundBox; }
	void AddComponent(Component* pComponent);
	void SetOwner(World* pOwner) { m_pOwner = pOwner; }
	void SetBoundBoxExtent(float width, float height) { m_BoundBox.SetExtent(width / 2, height / 2); }

	D2D1_VECTOR_2F GetWorldLocation();
	/*D2D_MATRIX_3X2_F GetWorldMatrix();
	void RenderMatrix(D2D_MATRIX_3X2_F mat);*/
	// 컴포넌트 를 템틀릿 함수로 생성합니다.
	template<typename T>
	T* CreateComponent()
	{
		bool bIsBase = std::is_base_of<Component, T>::value;
		assert(bIsBase == true);
		T* pComponent = new T();
		AddComponent(pComponent);
		return pComponent;
	}

	// 컴포넌트를 찾아서 반환합니다.
	template<typename T>
	T* GetComponent()
	{
		for (auto pComponent : m_OwnedComponents)
		{
			T* pT = dynamic_cast<T*>(pComponent);
			if (pT != nullptr)
			{
				return pT;
			}
		}
		return nullptr;
	}
};

