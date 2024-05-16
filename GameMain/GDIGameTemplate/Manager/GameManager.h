#pragma once
#include "../WinMain.h"

#include "../System/InputSystem.h"
#include "../System/TimeSystem.h"
#include "../System/RenderSystem.h"
#include "../System/SoundSystem.h"

#include "../Manager/SceneManager.h"

#include "../GameLogic/Animation.h"
#include "../GameLogic/Ranking.h"
namespace Game
{
	class GameManager
	{
	public:
		GameManager();

		~GameManager();

		void Initialize();

		void Update();

		void FixeUpdate();

		void Render();

		void Finalize();

		void Run();

		void LoadResource();

		void ReleaseResource();

		static GameManager* GetInstance();

		static void DestroyInstance();

	private:
		static GameManager* instance;
		SceneManager* m_sceneManager;
		CScene* m_curScene;
		Renking* i_renk;
		HWND m_hWnd = nullptr;
		HDC m_hdc = nullptr;
		int m_UpdateCount = { 0 };
		int m_FixedUpdateCount = { 0 };
	};
}

