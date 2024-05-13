#include "UIObject.h"
#include "../Event.h"
void UIObject::Init() {
	
}

void UIObject::Update(float delta) {

}

void UIObject::Render() {

}


void UIObject::OnTrigger()
{

}

void UIBackGround::Init() {
	m_BackGround = Gdiplus::Bitmap::FromFile(L"image1.png");
}

void UIBackGround::Render() {
	
	cx = m_BackGround->GetWidth();
	cy = m_BackGround->GetHeight();
	Render::DrawImage(100,100,m_BackGround,0,0,cx,cy);
}

void UIButton::Init(Vector2 myPos,Event* myEvent) {
	/*CResourceManager CR = CResourceManager::CResourceManager();
	m_Bitmap = CR.LoadBitmapResouce(L"버튼",L"sampleButton.png");*/
	m_pos = myPos;
	m_Event = myEvent;
	m_Bitmap = Gdiplus::Bitmap::FromFile(L"sampleButton.png");

	cx = m_Bitmap->GetWidth();
	cy = m_Bitmap->GetHeight();
	m_collider = new RectangleCollider({ 0.f,0.f }, { (float)cx, (float)cy });
	m_collider->parent = this;
}

void UIButton::Render() {
	Render::DrawImage(m_pos.x - m_renderBounds.extents.x, m_pos.y - m_renderBounds.extents.y, m_Bitmap, 0, 0, cx, cy);
}

void UIButton::OnTrigger() {
	if (m_Event != nullptr) m_Event->OnTrigger();
}

void UIButton::Update(float delta) {
	if (Input::GetMouseState().left && !Input::GetPrevMouseState().left) {
		Vector2 temp = Vector2(Input::GetMouseState().x, Input::GetMouseState().y);
		if(m_collider->isPointColliding(temp)) {
			OnTrigger();
		}
	}
}


void UITimer::Init(Vector2 myPos,Event* myEvent) {
	/*CResourceManager CR = CResourceManager::CResourceManager();
	m_Bitmap = CR.LoadBitmapResouce(L"버튼",L"sampleButton.png");*/
	m_pos = myPos;
	m_Event = myEvent;
	//m_Bitmap = Gdiplus::Bitmap::FromFile(L"sampleButton.png");

	//cx = m_Bitmap->GetWidth();
	//cy = m_Bitmap->GetHeight();
	cx = 400;
	cy = 100;
	//m_collider = new RectangleCollider({ 0.f,0.f }, { (float)cx, (float)cy });
	//m_collider->parent = this;
	deltaCx = 400;
}
void UITimer::Update(float delta) {
	setTime -= delta;
	std::cout << "delta : " << delta << endl;
	std::cout << "setTime : " << setTime << endl;
	//줄어든 바의 길이  = (정한시간에서 delta만크 줄어든 시기나 / 정한 시간 ) * 가로 길이 값
	if (setTime > 0) {
		deltaCx = (setTime / 60.0f) * cx;
	}
	else {
		OnTrigger();
		m_Event = nullptr;
	}
}	

void UITimer::Render() {
	Render::DrawRect(m_pos.x, m_pos.y, cx, cy, RGB(255, 255, 255));
	Render::DrawRect(m_pos.x, m_pos.y, (UINT)deltaCx, cy, RGB(255, 255, 0));
}

void UITimer::OnTrigger() {
	if (m_Event != nullptr) m_Event->OnTrigger();
}