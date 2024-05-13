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

	END = 32,
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
	void FixedUpdate();

	virtual void Start() = 0;
	virtual void Exit() = 0;

	ColliderManager* colliderManager; // 씬 전체 콜라이더를 관리하기 위함.
protected:
	//void AddObject(Object* obj, TYPE _type) {
	//	m_arrObj[(UINT)_type].push_back(obj); //이 코드 세철씨한테 물어볼 것.
	//}
	std::vector<Object*> m_arrObj;

	std::wstring m_strName;
	void AddObject(Object* obj);

public:
	CScene() {};
	virtual ~CScene() {};
};