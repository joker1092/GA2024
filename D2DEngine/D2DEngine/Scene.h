#pragma once
#include "framework.h"
#include "Component.h"
#include "D2DRender.h"

class D2DRender;
class Scene : public Component
{
public:
	Scene();
	virtual ~Scene();

	Scene* m_pParentScene = nullptr;		// 부모 Scene 컴포넌트	
	D2D_VECTOR_2F		m_RelativeScale = { 1,1 };	// 상대 크기
	float				m_RelativeRotation = 0; // 상대 회전
	D2D_VECTOR_2F 		m_RelativeLocation = { 0,0 }; // 상대 위치
	D2D_MATRIX_3X2_F	m_RelativeTransform; // 상대 복합 변환
	D2D_MATRIX_3X2_F	m_WorldTransform;    // 부모까지 반영된 최종 변환
	D2DRender* pD2DRender = nullptr;
	float width;
	float height;
	// RelativeTransform과 	m_WorldTransform을 계산한다.
	void UpdateTrasnform();
	void SetParentScene(Scene* pParentScene) { m_pParentScene = pParentScene; }
	D2D1_VECTOR_2F GetWorldLocation()
	{
		D2D1_VECTOR_2F out;
		out.x = m_WorldTransform._31;
		out.y = m_WorldTransform._32;
		return out;
	}
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1RenderTarget* pRenderTarget);
	void SetRelativeLocation(const D2D1_VECTOR_2F& Location);
	const D2D1_VECTOR_2F& GetRelativeLocation() { return m_RelativeLocation; }
};

 