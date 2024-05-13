#include "GameManager.h"



namespace Game
{
	
	Gdiplus::Bitmap* hTestBitmap = nullptr; // ���� ����
	GameManager* GameManager::instance = nullptr;
	mySound::SoundManager* SMInstance = mySound::SoundManager::GetInstance();
	GameManager::GameManager()
	{
	}
	GameManager::~GameManager()
	{
	}
	void GameManager::Initialize()
	{
		Input::InitInput();
		High_Resolution_Time::InitTime();
		SMInstance->LoadSounds(mySound::SoundList::Drum, false, "drumloop.wav");
		m_sceneManager = SceneManager::GetInstance();
		m_hWnd = global::GetWinApp().GetWindow();
		m_hdc = GetDC(m_hWnd);
		m_curScene = m_sceneManager->GetCurScene();
		LoadResource();
	}

	void GameManager::Update()
	{
		++m_UpdateCount;

		Input::UpdateMouse();
		if (m_curScene != m_sceneManager->GetCurScene()) {
			m_curScene = m_sceneManager->GetCurScene();
		}
		m_curScene->Update();
		Input::ResetInput();

		
	}
	
	void GameManager::FixeUpdate()
	{
		static ULONGLONG elapsedTime;

		elapsedTime += High_Resolution_Time::GetDeltaTime();
		
		while (elapsedTime >= 20) //0.02��
		{
			++m_FixedUpdateCount;
			
			m_curScene->FixedUpdate();

			elapsedTime -= 20;
		}
	}

	void GameManager::Render()
	{
		Render::BeginDraw();
		


		m_curScene->Render();

		Render::EndDraw();

		
	}
	void GameManager::Finalize()
	{

		Render::ReleaseRender();
		SMInstance->DestroyInstance();
	}
	void GameManager::Run()
	{
		MSG msg;


		while (true)
		{
			//GetMessage �� ť�� �޽����� ���� ������ ���, ��ŷ
			//PeekMessage �� �޽����� ������ ó���ϰ� �ƴϸ� �ͺ�ŷ
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT) break;

				if (msg.message == WM_KEYDOWN)
				{
					Input::KeyDown(msg.wParam);
				}
				else if (msg.message == WM_KEYUP)
				{
					Input::KeyUp(msg.wParam);
				}
				else
				{
					DispatchMessage(&msg);
				}
			}
			else
			{
				High_Resolution_Time::UpdateTime();

				FixeUpdate();

				Update();

				Render();

				
			}
		}
	}

	GameManager* GameManager::GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new GameManager();
		}
		return instance;
	}
	void GameManager::DestroyInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}


	
	//AnimationResource* g_PlayerAnim = nullptr;
	//void LoadResource()
	//{
	//	g_PlayerAnim = new AnimationResource;

	//	g_PlayerAnim->LoadAnimImage(L"../Resource/Ken.png");
	//	g_PlayerAnim->LoadAnimMotion(L"../Resource/KenIdle.txt");				 //	OBJECT_STATUS_IDLE,
	//	g_PlayerAnim->LoadAnimMotion(L"../Resource/KenMove.txt");				 //	OBJECT_STATUS_MOVE,
	//	g_PlayerAnim->LoadAnimMotion(L"../Resource/KenAttack.txt", false);		 //	OBJECT_STATUS_ATTACK

	//}

	//void ReleaseResource()
	//{
	//	delete g_PlayerAnim;
	//}

	void GameManager::LoadResource() {
		//hTestBitmap = Gdiplus::Bitmap::FromFile(L"image1.png");
	}

	void GameManager::ReleaseResource() {
		//delete hTestBitmap;
	}
	
}
