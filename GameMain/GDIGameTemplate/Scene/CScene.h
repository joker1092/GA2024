#pragma once
#include "../stdafx.h"
#include "../GameLogic/Vector2.h"
#include "../GameLogic/Objects/Object.h"

class ColliderManager;
enum class TYPE
{
	DEFAULT,

	PLAYER,
	FISH,
	UI,

	END = 5
};

//class ColliderManager;
class CScene
{
private:
	

public:
	void SetName(const std::wstring& _strName) { m_strName = _strName; }
	const std::wstring& GetName() { return m_strName; }
	virtual void Init() = 0; 
	void Update();
	void Render();
	virtual void FixedUpdate();

	virtual void Start() = 0;
	virtual void Exit() = 0;
	
	ColliderManager* colliderManager; // �� ��ü �ݶ��̴��� �����ϱ� ����.

	float alpha;					  // ����
protected:
	//void AddObject(Object* obj, TYPE _type) {
	//	m_arrObj[(UINT)_type].push_back(obj); //�� �ڵ� ��ö������ ��� ��.
	//}
	std::vector<Object*> m_arrObj;

	std::wstring m_strName;
	void AddObject(Object* obj);

public:
	CScene() {};
	~CScene() {
		for (int i = 0; i < m_arrObj.size(); i++) {

			if (m_arrObj[i] != nullptr) {
				delete m_arrObj[i];
			}
		}
		m_arrObj.clear();
		if (colliderManager != nullptr)
			delete colliderManager;
	};
};