#pragma once

#include "resource.h"

namespace game {
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

		static GameManager* GetInstance();

		static void DestroyInstance();

	private:
		void initMap();
		
		void DrawBack();
		void DrawFPS();
		void DrawPlayer();
		void DrawEnemy();
		void DrawSomething();

		void Load(const char* path, HBITMAP* bitmap);
		void Upload(HBITMAP bitmap);

		static GameManager* instance;

		int m_UpdateCount = { 0 };
		int m_FixedUpdateCount = { 0 };
	};
}


