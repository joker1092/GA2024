#pragma once
#include "Object.h"
//#include "../Event.h"
#define BACK_GROUND_ANIM_FRAME 60

class UIObject : public Object
{
	// Object을(를) 통해 상속됨
	void Init() override;
	//void Update(float delta) override;
	void Render(float alpha) override;
	//void SetMotion(int index)override;
	//void UpdateAnimation(float delta)override;
	//void ChangeStatus(ObjectStatus status)override;
	void OnTrigger() override;

public:
	float alpha = 1.f;
};

class UIImage : public UIObject
{
	// Object을(를) 통해 상속됨
public:
	void Init(Gdiplus::Bitmap* myBitMap , Vector2 myVector);
	UIImage() {};
	~UIImage() override {};//{ delete m_BackGround; }
	//void Update(float delta) override;
	void Render(float alpha) override;
	//void SetMotion(int index)override;
	//void UpdateAnimation(float delta)override;
	//void ChangeStatus(ObjectStatus status)override;
	//void OnTrigger() override;
private:
	Gdiplus::Bitmap* m_BackGround;
};

class UIButton : public UIObject
{
	// Object을(를) 통해 상속됨
public:
	void Init(Vector2 myPos, Event* myEvent, Gdiplus::Bitmap* myBitMap);
	

	UIButton(Vector2 myPos, Event* myEvent, Gdiplus::Bitmap* myBitMap) {
		Init(myPos,myEvent, myBitMap);
		m_Event = myEvent;
		m_renderBounds = { {0.f, 0.f },{(float)x,(float)y} };
	}
	void Update(float delta) override;
	void Render(float alpha) override;
	//void SetMotion(int index)override;
	//void UpdateAnimation(float delta)override;
	//void ChangeStatus(ObjectStatus status)override;
	void OnTrigger() override;
	~UIButton() override {}; /*{
		delete m_Bitmap;
	}*/
	
private:
	Gdiplus::Bitmap* m_Bitmap;
	UINT cx = 0;
	UINT cy = 0;
	UINT x = 120;
	UINT y = 90;
};

// scnene init
//sceneTimer = new UITimer(Vector2{ x, y });
// scenen update 
//sceneTimer->Update(High_Resolution_Time::GetDeltaTime() / 1000.0f);
class UITimer : public UIObject
{
	// Object을(를) 통해 상속됨
public:
	void Init(Vector2 myPos,Event* myEvent,float _setTime);


	UITimer(Vector2 myPos, Event* myEvent,float _setTime) {
		Init(myPos,myEvent,_setTime);
		//m_Event = myEvent;
		//m_renderBounds = { {(float)cx,(float)cy},{(float)x,(float)y} };
	}
	void Update(float delta) override;
	void Render(float alpha) override;
	//void SetMotion(int index)override;
	//void UpdateAnimation(float delta)override;
	//void ChangeStatus(ObjectStatus status)override;
	void OnTrigger() override;
	~UITimer() override {}; /*{
		delete m_Bitmap;
	}*/

private:
	Gdiplus::Bitmap* m_Bitmap;
	UINT cx;
	UINT cy;
	UINT x;
	UINT y;
	float deltaCx;
	float setTime;
	float deltaTime;
};

class UIBackGround : public UIObject
{
private:
	std::wstring m_fileName[BACK_GROUND_ANIM_FRAME];
	Gdiplus::Bitmap* m_bitmap[BACK_GROUND_ANIM_FRAME] = { nullptr, };
	int backGroundFrame;
	int backGroundFrameFlag;
	const static int backGroundFrameInterval = 10;

	float time = 0.f;
	float maxTime = 0.2f;
public:
	// Object을(를) 통해 상속됨
	void Init(const WCHAR* fileName, CResourceManager* CRM);
	void Update(float delta) override;
	void Render(float alpha) override;
	void FixedUpdate();
	//void SetMotion(int index)override;
	//void UpdateAnimation(float delta)override;
	//void ChangeStatus(ObjectStatus status)override;
	//void OnTrigger() override;
	~UIBackGround() override {};
	void LoadAnimImage(const WCHAR* fileName, CResourceManager* CRM);
	

};

class UIDialog : public UIObject {
private:
	UINT cx = 0;
	UINT cy = 0;
	UINT x = 0;
	UINT y = 0;
	WCHAR* string;
	COLORREF color;
	int fontSize;
public:
	~UIDialog()override {
		delete[] string;
	};
	void Init(Vector2 myPos, Vector2 endPos,WCHAR* _string, COLORREF _color, int _fontSize);
	void Update(float delta) override;
	void Render(float alpha)override;
	void OnTrigger() override;
};

class UICrossDissolve : public UIObject {
	Gdiplus::Bitmap* m_BackGround;
	float alphaValue;
public:
	UICrossDissolve(Vector2 position, Gdiplus::Bitmap* bitmap);
	void Init();
	void Update(float delta) override;
	void Render(float alpha) override;
};