#include "UIObject.h"
#include "../Event.h"


void UIObject::Init() {

}

void UIObject::Render(float alpha) 
{
	
}


void UIObject::OnTrigger()
{

}

void UIImage::Init(Gdiplus::Bitmap* myBitMap, Vector2 myVector) {
	//CResourceManager* CR = CResourceManager::GetInstance();
	//m_BackGround = CR->LoadBitmapResouce(L"image1",L"image1.png");
	//m_BackGround = Gdiplus::Bitmap::FromFile(L"image1.png");
	m_BackGround = myBitMap;
	if (m_BackGround == nullptr) return;
	m_renderBounds = { {0.f, 0.f}, {myBitMap->GetWidth() / 2.f, myBitMap->GetHeight() / 2.f} };
	m_pos = myVector;
}

void UIImage::Render(float _alpha) {
	if (m_isActive == false) return;
	//0x00000147f3f723d0
	if (m_BackGround == nullptr) return;
	Render::DrawImage(m_pos.x- m_renderBounds.extents.x, m_pos.y - m_renderBounds.extents.y, m_BackGround, 0, 0, m_renderBounds.extents.x * 2, m_renderBounds.extents.y * 2 , alpha);
}
//���� - ���� - ��ư - �⺻ - 1	200 * 100
void UIButton::Init(Vector2 myPos, Event* myEvent, Gdiplus::Bitmap* myBitMap) {
	/*CResourceManager CR = CResourceManager::CResourceManager();
	m_Bitmap = CR.LoadBitmapResouce(L"��ư",L"sampleButton.png");*/
	m_pos = myPos;
	m_Event = myEvent;
	m_Bitmap = myBitMap;
	if (m_Bitmap == nullptr) return;
	cx = m_Bitmap->GetWidth();
	cy = m_Bitmap->GetHeight();
	m_collider = new RectangleCollider({ 0.f,0.f }, { (float)cx, (float)cy });
	m_collider->parent = this;
}

void UIButton::Render(float alpha) {
	if (m_isActive == false) return;
	Render::DrawImage(m_pos.x - m_renderBounds.extents.x, m_pos.y - m_renderBounds.extents.y, m_Bitmap, 0, 0, cx, cy, 1.0f);
}

void UIButton::OnTrigger() {
	if (m_Event != nullptr) m_Event->OnTrigger();
}

void UIButton::Update(float delta) {
	if (m_isActive == false) return;
	if (Input::GetMouseState().left && !Input::GetPrevMouseState().left) {
		Vector2 temp = Vector2(Input::GetMouseState().x, Input::GetMouseState().y);
		if (m_collider->isPointColliding(temp)) {
			OnTrigger();
		}
	}
}

//����-�ð�-������-��-������-1	600*50
//���� - �ð� - ������ - �� - ��� - 1	600 * 50
void UITimer::Init(Vector2 myPos, Event* myEvent,float _setTime) {
	/*CResourceManager CR = CResourceManager::CResourceManager();
	m_Bitmap = CR.LoadBitmapResouce(L"��ư",L"sampleButton.png");*/
	//m_Bitmap = Gdiplus::Bitmap::FromFile(L"sampleButton.png");
	m_pos = myPos;
	m_Event = myEvent;
	
	cx = 600;
	cy = 50;
	
	deltaCx = 600;
	setTime = _setTime;
	deltaTime = _setTime;
}
void UITimer::Update(float delta) {
	if (m_isActive == false) return;
	deltaTime -= delta;
	/*std::cout << "delta : " << delta << endl;
	std::cout << "setTime : " << setTime << endl;*/
	//�پ�� ���� ����  = (���ѽð����� delta��ũ �پ�� �ñ⳪ / ���� �ð� ) * ���� ���� ��
	if (deltaTime > 0) {

		deltaCx = (deltaTime / setTime) * cx;

	}
	else {
		OnTrigger();
	}
}

void UITimer::Render(float alpha) {
	if (m_isActive == false) return;
	Render::DrawRect(m_pos.x, m_pos.y, cx, cy, RGB(255, 255, 255));
	Render::DrawRect(m_pos.x, m_pos.y, (UINT)deltaCx, cy, RGB(255, 255, 0));
}

void UITimer::OnTrigger() {
	if (m_Event != nullptr) m_Event->OnTrigger();
}

void UIBackGround::Init(const WCHAR* fileName, CResourceManager* CRM) {
	LoadAnimImage(fileName,CRM);
	m_pos = { 960.f, 540.f };
	m_renderBounds = { {0,0},{m_bitmap[0]->GetWidth() / 2.f,m_bitmap[0]->GetHeight() / 2.f} };
	backGroundFrame = 0;
	backGroundFrameFlag = 0;
}

void UIBackGround::LoadAnimImage(const WCHAR* fileName,CResourceManager* CRM)
{
	int fileNameLength = wcslen(fileName);
	
	m_fileName[0] = fileName;
	m_bitmap[0] = CRM->LoadBitmapResouce(fileName, fileName);
	std::wstring noNumFileName = m_fileName[0].substr(0, fileNameLength - 6);

	for (int i = 1; i < BACK_GROUND_ANIM_FRAME; i++) {
		std::wstring wZero = std::to_wstring(0);
		
		std::wstring wNum = std::to_wstring(i);
		if (i < 10) {
			m_fileName[i] = noNumFileName.append(wZero).append(wNum);
		}
		else {
			m_fileName[i] = noNumFileName.append(wNum);
		}
		
		m_bitmap[i] = CRM->LoadBitmapResouce(m_fileName[i].c_str(), m_fileName[i].append(L".png").c_str());
		noNumFileName = noNumFileName.substr(0, fileNameLength - 6);
	}


}

void UIBackGround::Update(float delta) {
	time += delta;
	if (time >= maxTime) {
		time -= maxTime;
		backGroundFrame = (backGroundFrame + 1) % BACK_GROUND_ANIM_FRAME;
	}

	/*backGroundFrameFlag = ++backGroundFrameFlag % backGroundFrameInterval;
	if (backGroundFrameFlag == 9) {
		backGroundFrame = ++backGroundFrame % BACK_GROUND_ANIM_FRAME;
	}*/
}

void UIBackGround::Render(float alpha) {
	
	/*Render::DrawImage(m_pos.x - m_renderBounds.extents.x, 
		m_pos.y - m_renderBounds.extents.y, m_bitmap[backGroundFrame], 
		0, 0, m_renderBounds.extents.x * 2, m_renderBounds.extents.y * 2);*/

	//Render::DrawImage(50, 200, m_bitmap[backGroundFrame], 0, 0, 1250, 800);
	Render::DrawBitmap(0, 0, m_bitmap[backGroundFrame], 0, 0, 1280, 720);
	
}

void UIBackGround::FixedUpdate() {
	
	
}


//UIBackGround::~UIBackGround() {
//	for (int i = 0; i < BACK_GROUND_ANIM_FRAME; i++) {
//		if (m_bitmap[i]!=nullptr)
//			delete m_bitmap[i];
//	}
//}


void UIDialog::Init(Vector2 myPos, Vector2 endPos, WCHAR* _string,COLORREF _color ,int _fontSize) {
	x = myPos.x;
	y = myPos.y;
	cx = endPos.x;
	cy = endPos.y;
	string = _string;
	color = _color;
	fontSize = _fontSize;
}
void UIDialog::Render(float alpha){
	Render::DrawFont(x, y, cx, cx, string, color, fontSize , L"Arial", 1);
}

void UIDialog::Update(float delta) {
	
}

void UIDialog::OnTrigger() {

}

UICrossDissolve::UICrossDissolve(Vector2 position, Gdiplus::Bitmap* bitmap)
{
	m_pos = position;
	m_BackGround = bitmap;
	Init();
}

void UICrossDissolve::Init()
{
	alphaValue = 1.f;
	if (m_BackGround == nullptr) return;
	m_renderBounds = { {0.f, 0.f}, {m_BackGround->GetWidth() / 2.f, m_BackGround->GetHeight() / 2.f} };
}

void UICrossDissolve::Update(float delta)
{
	if (m_isActive == false) return;
	alphaValue -= delta;
	if (alphaValue < 0.f) {
		alphaValue = 0;
		m_isActive = false;
	}
}

void UICrossDissolve::Render(float alpha)
{
	if (m_isActive == false) return;
	if (m_BackGround == nullptr) return;
	Render::DrawImage(m_pos.x - m_renderBounds.extents.x, m_pos.y - m_renderBounds.extents.y, m_BackGround, 0, 0, m_renderBounds.extents.x * 2, m_renderBounds.extents.y * 2, alphaValue);
}
