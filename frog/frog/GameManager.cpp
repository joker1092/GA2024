#include "WinApp.h"
#include "TimeSystem.h"
#include "InputSystem.h"
#include "RenderSystem.h"
#include "Object.h"
#include "GameManager.h"

#include <string>

enum state
{
	READY,
	START,
	GAMEOVER,
	QUIT
};



namespace game {

	TimeSystem time;
	InputSystem input;
	RenderSystem render;
	Object player;

	HBITMAP hBackBitmap = nullptr;

	void UpdatePlayer()
	{
		// 게임 로직은 여기에 추가
		if (input.IsKey('A'))
		{
			player.Move(-player.speed*time.GetDeltaTime(), 0);
		}
		else if (input.IsKey('D'))
		{
			player.Move(player.speed * time.GetDeltaTime(), 0);
		}
		if (input.IsKey('W'))
		{
			player.Move(0, -player.speed * time.GetDeltaTime());
		}
		else if (input.IsKey('S'))
		{
			player.Move(0, player.speed * time.GetDeltaTime());
		}
	}

	GameManager* GameManager::instance = nullptr;
	GameManager::GameManager()
	{
	}
	GameManager::~GameManager()
	{
	}

	void GameManager::Initialize()
	{
		time.InitTime();
		input.InitInput();
		render.InitRender();

		player.InitObject(global::GetWinApp().GetWidth() / 2.f, global::GetWinApp().GetHeight() / 2.f, 10, 10, 0.3f, nullptr);
		Load(".\\assets\\marine.bmp", &player.pBitmap);
	}

	void GameManager::Update()
	{
		++m_UpdateCount;

		input.UpdateMouse();
		time.UpdateTime();
		
		UpdatePlayer();
		//UpdateBlueCircle();

		input.ResetInput();
	}

	void GameManager::FixeUpdate()
	{
		static float elapsedTime;

		elapsedTime += time.GetDeltaTime();

		while (elapsedTime >= 100) //0.02초
		{
			++m_FixedUpdateCount;

			elapsedTime -= 20;
		}
	}

	void GameManager::Render()
	{
		render.BeginDraw();
		DrawBack();
		DrawFPS();
		DrawSomething();
		DrawPlayer();
		DrawEnemy();

		render.EndDraw();
	}
	void GameManager::Finalize()
	{

		Upload(player.pBitmap);
		/*Upload(enemy.pBitmap);
		Upload(hTestBitmap);*/

		render.ReleaseRender();
	}
	void GameManager::Run()
	{
		MSG msg;

		while (true)
		{
			// GetMessage 가 아니라 PeekMessage 를 사용합니다!!
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT) break;

				if (msg.message == WM_KEYDOWN)
				{
					input.KeyDown(msg.wParam);
				}
				else if (msg.message == WM_KEYUP)
				{
					input.KeyUp(msg.wParam);
				}
				else
				{
					DispatchMessage(&msg);
				}
			}
			else
			{
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

	void GameManager::DrawFPS()
	{
		static ULONGLONG elapsedTime;
		static int UpdateCount;
		static int FixedUpdateCount;

		elapsedTime += time.GetDeltaTime();

		if (elapsedTime >= 20)
		{
			elapsedTime = 0;
			;
			UpdateCount = m_UpdateCount;
			FixedUpdateCount = m_FixedUpdateCount;

			m_UpdateCount = 0;
			m_FixedUpdateCount = 0;
		}

		std::string str = "FPS: " + std::to_string(time.GetFrameRate());
		str += "           Update " + std::to_string(UpdateCount);
		str += "           FixedUpdate " + std::to_string(FixedUpdateCount);

		render.DrawText(10, 10, str.c_str(), RGB(255, 0, 0));

	}

	void GameManager::DrawBack() {
		render.DrawBitmap(0, 0, hBackBitmap);
	}

	void GameManager::DrawPlayer()
	{
		render.DrawBitmap(player.x, player.y, player.pBitmap);
	}

	void GameManager::DrawEnemy()
	{
		//render.DrawBitmap(enemy.x, enemy.y, enemy.pBitmap);
	}

	void GameManager::DrawSomething()
	{
		/*for (int i = 0; i < blueCircleCount; i++)
		{
			render::DrawCircle(blueCircles[i].x, blueCircles[i].y, blueCircles[i].size, blueCircles[i].color);
		}

		if (state)
		{
			render::DrawRect(player.x - 25, player.y - 25, 50, 50, RGB(255, 0, 255));
		}*/
		//render::DrawLine(player.x - 50, player.y + 50, player.x + 50, player.y + 50, RGB(255, 0, 0));
		//render::DrawRect(player.x - 25, player.y - 25, 50, 50, RGB(255, 0, 255));
		//render.DrawBitmap(50, 50, hTestBitmap);

	}
	void GameManager::Load(const char* path, HBITMAP* bitmap) {
		//const char* path = ".\\assets\\sample.bmp";
		*bitmap = render.LoadImdage(path);
	}
	void GameManager::Upload(HBITMAP bitmap) {
		render.ReleaseImage(bitmap);
	}

	//bool GameManager::isRectEnter() {
		/*<if (player.x + player.size < enemy.x || player.x>enemy.x + enemy.size || player.y + player.size<enemy.y || player.y>enemy.y + enemy.size)
		{
			return false;
		}
		else {
			return true;
		}*/

	//}
}


