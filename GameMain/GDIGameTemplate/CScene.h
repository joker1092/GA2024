#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include "Vector2.h"

enum class TYPE
{
	DEFAULT,

	PLAYER,
	FISH,
	UI,

	END = 32,
};


class CObject {
private:
	Vector2 m_Pos;
	Vector2 m_Scale;
public:
	Vector2 GetPos() { return m_Pos; }
	Vector2 GetScale() { return m_Scale; }

	void SetPos(Vector2 pos) { m_Pos = pos; }
	void SetScale(Vector2 scale) { m_Scale = scale; }
public:
	virtual void Update()=0;
	virtual void Render(HDC dc)=0;
public:
	CObject();
	virtual ~CObject();
};


class CScene
{
private:
	std::vector<CObject*> m_arrObj[(UINT)TYPE::END];
	std::wstring m_strName;
public:
	void SetName(const std::wstring& _strName) { m_strName = _strName; }
	const std::wstring& GetName() { return m_strName; }

	virtual void Update() = 0;
	virtual void Render(HDC dc) = 0;

	virtual void Start() = 0;
	virtual void Exit() = 0;

protected:
	void AddObject(CObject* obj, TYPE _type) {
		m_arrObj[(UINT)_type].push_back(obj);
	}

public:
	CScene() {};
	~CScene() {};
};

// void CScene::Update() {
//	for (UINT i = 0; i < (UINT)TYPE::END; ++i) {
//		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
//		{
//			m_arrObj[i][j]->Update();
//		}
//	}
//}
//
//void CScene::Render(HDC dc) {
//	for (UINT i = 0; i < (UINT)TYPE::END; ++i) {
//		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
//		{
//			m_arrObj[i][j]->Render(dc);
//		}
//	}
//}