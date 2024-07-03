#include "framework.h"
#include "World.h"


World::World()
{
	// 화면크기 정보를 가져와서
	float width = 1920;
	float height = 1280;
	m_CullingBoundDefault.SetExtent(width / 2, height / 2);
	m_CullingBoundDefault.SetCenter(0, 0);
	SetCullingBound(&m_CullingBoundDefault);
	// 카메라를 생성한다.
	m_pCamera = new Camera();
	m_pCamera->SetLocation({ width / 2, height / 2 });
}

World::~World()
{
	delete m_pCamera;
}


void World::Update(float deltaTime)
{
	// 카메라의 업데이트를 먼저하고
	m_pCamera->Update(deltaTime);
	SetCullingBound(m_pCamera->GetViewBoundBox());
	for (auto& obj : m_GameObjects)
	{
		obj->Update(deltaTime);
	}
}


bool RenderSortOrder(GameObject* a, GameObject* b)
{
	return a->m_ZOrder > b->m_ZOrder;
}


void World::Render(ID2D1RenderTarget* pRenderTarget, ID2D1SolidColorBrush* brush)
{
	// 이건 컬링 테스트 없이 전부 Render 하는것
	/*for (auto& obj : m_GameObjects){
		obj->Render(pRenderTarget);
	}*/
	// 컬링 테스트를 하기 위해서


	
	objectCount= m_GameObjects.size();
	for (auto& obj : m_GameObjects) {
		
		if (m_pCullingBound->CheckIntersect(obj->m_BoundBox)) {
			m_RenderQueue.push_back(obj);
		}
	}
	std::sort(m_RenderQueue.begin(), m_RenderQueue.end(), RenderSortOrder);
	// 카메라의 역행렬을 구해서
	D2D_MATRIX_3X2_F mat = m_pCamera->GetCameraMatrix();
	D2D1InvertMatrix(&mat);
	D2D1_RECT_F boundRect = { m_pCullingBound->GetMinX(),m_pCullingBound->GetMinY(),m_pCullingBound->GetMaxX(),m_pCullingBound->GetMaxY() };
	pRenderTarget->DrawRectangle(boundRect, brush, 1.0f);
	renderCount = m_RenderQueue.size();
	for (auto& obj : m_RenderQueue){
		obj->m_pRootScene->mWorldTransform = obj->m_pRootScene->mWorldTransform * mat;
		D2D1_RECT_F rc = { obj->m_BoundBox.GetMinX(),obj->m_BoundBox.GetMinY(),obj->m_BoundBox.GetMaxX(),obj->m_BoundBox.GetMaxY() };
		pRenderTarget->DrawRectangle(rc,brush,1.0f);
		obj->Render(pRenderTarget);
	}
	m_RenderQueue.clear();
}

void World::Clear()
{
	m_GameObjects.clear();
}

