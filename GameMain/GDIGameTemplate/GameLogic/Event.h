#pragma once
#include "../Manager/SceneManager.h"
#include "../Manager/GameManager.h"
#include "../Scene/CScene.h"
#include "../System/TimeSystem.h"
#include "../System/SoundSystem.h"

class Event {
public:
	virtual void Init() {};
	virtual void OnTrigger() = 0;
	Event() { 
		/*m_SoundManager = mySound::SoundManager::GetInstance();
		m_Sound = mySound::SoundList::Void; */
	}
	Event(mySound::SoundList mSound) { 
		/*m_SoundManager = mySound::SoundManager::GetInstance();
		m_Sound = mSound; */
	}
	virtual ~Event() { 
		std::cout << "d이벤트 소멸" << std::endl; 
	}
protected:
	/*mySound::SoundManager* m_SoundManager = nullptr;
	mySound::SoundList m_Sound = mySound::SoundList::Void;*/
};

class SelectScnEvent : public Event {
private:
	SceneManager* scnManager;
	Game::GameManager* gameManager;
	int nextSceneNum;

public:
	/*SelectScnEvent() {
		Init();
	}*/

	SelectScnEvent(int sceneNum) {
		scnManager = SceneManager::GetInstance();
		gameManager = Game::GameManager::GetInstance();
		mySound::SoundManager::GetInstance();
		nextSceneNum = sceneNum;
		//m_Sound = mySound::SoundList::Void;
	}

	SelectScnEvent(int sceneNum, mySound::SoundList mSound) {
		scnManager = SceneManager::GetInstance();
		gameManager = Game::GameManager::GetInstance();
		mySound::SoundManager::GetInstance();
		nextSceneNum = sceneNum;
		//m_Sound = mSound;
	}

	/*void Init() override {
		scnManager = SceneManager::GetInstance();
		
		
	}*/

	void OnTrigger() override {
		SelectScene(nextSceneNum);
		//if (m_Sound != mySound::SoundList::Void) {
			//m_SoundManager->PlaySounds(m_Sound,mySound::SoundChannel::Effect);
		//}
	}

	void SelectScene(int i) {
		scnManager->SetCurScene(i);
	}
	~SelectScnEvent() {
		std::cout << "d이벤트 소멸dwadawdawd" << std::endl;
	}
};

class PauseEvent : public Event
{
public:

	UIImage* PauseBack;
	UIButton* Resume;
	UIButton* Retry;
	UIButton* Exit;
	
	void OnTrigger() override
	{
		PauseBack->m_isActive = true;
		Resume->m_isActive = true;
		Retry->m_isActive = true;
		Exit->m_isActive = true;
		High_Resolution_Time::SetTimeScale(0.f);
	}

};

class ResumeEvent : public Event
{	
public:
	UIImage* PauseBack;
	UIButton* Resume;
	UIButton* Retry;
	UIButton* Exit;

	void OnTrigger() override
	{
		PauseBack->m_isActive = false;
		Resume->m_isActive = false;
		Retry->m_isActive = false;
		Exit->m_isActive = false;
		High_Resolution_Time::SetTimeScale(1.f);
	}
};

class RetryEvent : public Event
{
	// retry 버튼을 눌렀을때 그냥 맨처음 초기화면으로 돌아가게끔
	// + 시간초가 다되면 retry 이벤트가 자동으로 실행되게끔

private:
	SceneManager* scnManager = SceneManager::GetInstance();
	Game::GameManager* gameManager = Game::GameManager::GetInstance();

public:

	void OnTrigger() override
	{	
		scnManager->SetCurScene(1);
		High_Resolution_Time::SetTimeScale(1.f);
	}
};

class ExitEvent : public Event
{
	void OnTrigger() override
	{	
		_CrtDumpMemoryLeaks();
		PostQuitMessage(1);
	}
};

class Discription : public Event
{
public:
	UIButton* Close;
	UIButton* Resume;

	void OnTrigger() override
	{	
		Close->m_isActive = true;
		Resume->m_isActive = true;
		High_Resolution_Time::SetTimeScale(0.f);
	}
};