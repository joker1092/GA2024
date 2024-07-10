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
	std::vector<Component*> m_OwnedComponents;	// ������ ������Ʈ��
	Scene* m_pRootScene = nullptr;				// ������Ʈ �߿� ����� ��Ʈ���� ����
	World* m_pOwner = nullptr;					// �� ���� ������Ʈ�� ���� ����
	AABB m_BoundBox;								// �ٿ�� �ڽ�
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
	// ������Ʈ �� ��Ʋ�� �Լ��� �����մϴ�.
	template<typename T>
	T* CreateComponent()
	{
		bool bIsBase = std::is_base_of<Component, T>::value;
		assert(bIsBase == true);
		T* pComponent = new T();
		AddComponent(pComponent);
		return pComponent;
	}

	// ������Ʈ�� ã�Ƽ� ��ȯ�մϴ�.
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

