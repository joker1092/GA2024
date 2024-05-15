#pragma once
#include "Object.h"
//#include "../Event.h"
#define BACK_GROUND_ANIM_FRAME 10

class UIObject : public Object
{
	// Object을(를) 통해 상속됨
	void Init() override;
	//void Update(float delta) override;
	void Render()override;
	//void SetMotion(int index)override;
	//void UpdateAnimation(float delta)override;
	//void ChangeStatus(ObjectStatus status)override;
	void OnTrigger() override;
};

class UIImage : public UIObject
{
	// Object을(를) 통해 상속됨
public:
	void Init(Gdiplus::Bitmap* myBitMap , Vector2 myVector);
	UIImage() {};
	~UIImage() { delete m_BackGround; }
	//void Update(float delta) override;
	void Render();
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
	void Init(Vector2 myPos, Event* myEvent);
	

	UIButton(Vector2 myPos, Event* myEvent) {
		Init(myPos,myEvent);
		m_Event = myEvent;
		m_renderBounds = { {0.f, 0.f },{(float)x,(float)y} };
	}
	void Update(float delta) override;
	void Render()override;
	//void SetMotion(int index)override;
	//void UpdateAnimation(float delta)override;
	//void ChangeStatus(ObjectStatus status)override;
	void OnTrigger() override;
	~UIButton() {
		delete m_Bitmap;
		delete m_Event;
	}
	
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
	void Init(Vector2 myPos,Event* myEvent);


	UITimer(Vector2 myPos, Event* myEvent) {
		Init(myPos,myEvent);
		//m_Event = myEvent;
		//m_renderBounds = { {(float)cx,(float)cy},{(float)x,(float)y} };
	}
	void Update(float delta) override;
	void Render()override;
	//void SetMotion(int index)override;
	//void UpdateAnimation(float delta)override;
	//void ChangeStatus(ObjectStatus status)override;
	void OnTrigger() override;


private:
	Gdiplus::Bitmap* m_Bitmap;
	UINT cx = 0;
	UINT cy = 0;
	UINT x = 1600;
	UINT y = 800;
	float deltaCx = 1600.0f;
	float setTime = 60.0f;
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
	void Render()override;
	void FixedUpdate();
	//void SetMotion(int index)override;
	//void UpdateAnimation(float delta)override;
	//void ChangeStatus(ObjectStatus status)override;
	//void OnTrigger() override;
	~UIBackGround();
	void LoadAnimImage(const WCHAR* fileName, CResourceManager* CRM);
	

};

class UIDialog : public UIObject {
private:
	UINT cx = 0;
	UINT cy = 0;
	UINT x = 0;
	UINT y = 0;
	WCHAR* string;
public:
	void Init(Vector2 myPos, Vector2 endPos,WCHAR* _string);
	void Update(float delta) override;
	void Render()override;
	void OnTrigger() override;
};
