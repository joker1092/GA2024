

#include "GameManager.h"

#include <string>

namespace Game
{
	

	GameManager* GameManager::instance = nullptr;
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
		mySound::InitFMOD();
		mySound::LoadSounds();
		startScene = new StartScene();
		m_hWnd = global::GetWinApp().GetWindow();
	}

	void GameManager::Update()
	{
		++m_UpdateCount;

		Input::UpdateMouse();

		Input::ResetInput();
		mySound::PlaySounds(0);
	}

	void GameManager::FixeUpdate()
	{
		static ULONGLONG elapsedTime;

		elapsedTime += High_Resolution_Time::GetDeltaTime();

		while (elapsedTime >= 20) //0.02��
		{
			++m_FixedUpdateCount;

			elapsedTime -= 20;
		}
	}

	void GameManager::Render()
	{
		Render::BeginDraw();
		HDC hdc =  GetDC(m_hWnd);
		startScene->Render(hdc);

		Render::EndDraw();

		
	}
	void GameManager::Finalize()
	{

		Render::ReleaseRender();
		mySound::ReleaseSounds();
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


	HBITMAP hTestBitmap = nullptr; // ���� ����

	

	
}
