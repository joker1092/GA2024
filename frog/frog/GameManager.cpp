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

enum BackDraw {
	END,
	WATER,
	GREEN,
	LOAD,
	POSITION,
};

const int CAR1_INDEX = 3;
const int CAR2_INDEX = 2;
const int CAR3_INDEX = 4;
const int CAR4_INDEX = 2;

const int WOOD1_INDEX = 4;
const int WOOD2_INDEX = 3;
const int WOOD3_INDEX = 2;

const int block = 80;

namespace game {

	TimeSystem time;
	InputSystem input;
	RenderSystem render;
	Object player;

	Object car1[CAR1_INDEX];
	Object car2[CAR2_INDEX];
	Object car3[CAR3_INDEX];
	Object car4[CAR4_INDEX];

	Object wood1[WOOD1_INDEX];
	Object wood2[WOOD2_INDEX];
	Object wood3[WOOD3_INDEX];

	HBITMAP hBackBitmap = nullptr;
	RECT playRect;

	HBITMAP hBitmap_end = nullptr;
	HBITMAP hBitmap_water = nullptr;
	HBITMAP hBitmap_green = nullptr;
	HBITMAP hBitmap_load = nullptr;
	HBITMAP hBitmap_start = nullptr;

	struct bound {
		int x;
		int y;
		int state = 0;
		BackDraw draw;
	};

	bound Map[10][10];

	bool Clamp(int x, int y) {
		int offsetx = 10;
		int offsety = 10;
		int playbleWidth = 800-block;
		int playbleheight = 800 - block;

		return (x<offsetx || y<offsety || x>(offsetx + playbleWidth) || y>(offsety + playbleheight));
	}


	void UpdatePlayer()
	{
		

		// 게임 로직은 여기에 추가
		/*if (input.IsKey('A'))
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
		}*/
		if (input.IsKeyDown('A'))
		{
			player.Move(-block, 0);
			if (Clamp(player.x, player.y)) {
				player.SetPos(player.x + block, player.y);
			}
		}
		else if (input.IsKeyDown('D'))
		{
			player.Move(block, 0);
			if (Clamp(player.x, player.y)) {
				player.SetPos(player.x - block, player.y);
			}
		}
		if (input.IsKeyDown('W'))
		{
			player.Move(0, -block);
			if (Clamp(player.x, player.y)) {
				player.SetPos(player.x , player.y + block);
			}
		}
		else if (input.IsKeyDown('S'))
		{
			player.Move(0, block);
			if (Clamp(player.x, player.y)) {
				player.SetPos(player.x , player.y - block);
			}
		}
	}

	void UpdateEnemy()
	{
		for (int i = 0; i < CAR1_INDEX; i++)
		{
			car1[i].Move(-car1[i].speed, 0);
			if (car1[i].x+160 < 10)
			{
				car1[i].SetPos(800, car1->y);
			}
		}
		for (int i = 0; i < CAR2_INDEX; i++)
		{
			car2[i].Move(car2[i].speed, 0);
			if (car2[i].x  > 800)
			{
				car2[i].SetPos(-160, car2->y);
			}
		}
		for (int i = 0; i < CAR3_INDEX; i++)
		{
			car3[i].Move(-car3[i].speed, 0);
			if (car3[i].x + 160 < 10)
			{
				car3[i].SetPos(800, car3->y);
			}
		}
		for (int i = 0; i < CAR4_INDEX; i++)
		{
			car4[i].Move(car4[i].speed, 0);
			if (car4[i].x  > 800)
			{
				car4[i].SetPos(-320, car4->y);
			}
		}
	}

	void GameManager::initMap() {
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				Map[i][j].x = j;
				Map[i][j].y = i;

				switch (i)
				{
				case 0:
					Map[i][j].draw = END;
					break;
				case 1:
				case 2:
				case 3:
					Map[i][j].draw = WATER;
					break;
				case 4:
					Map[i][j].draw = GREEN;
					break;
				case 5:
				case 6:
				case 7:
				case 8:
					Map[i][j].draw = LOAD;
					break;
				case 9:
					Map[i][j].draw = POSITION;
					break;
				default:
					break;
				}
			}
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
		initMap();
		Load(".\\assets\\end.bmp", &hBitmap_end);
		Load(".\\assets\\water.bmp", &hBitmap_water);
		Load(".\\assets\\green.bmp", &hBitmap_green);
		Load(".\\assets\\load.bmp", &hBitmap_load);
		Load(".\\assets\\start.bmp", &hBitmap_start);
		player.InitObject(410, 730, 80, 80, 0.3f, nullptr);
		Load(".\\assets\\frog_up.bmp", &player.pBitmap);

		for (int i = 0; i < CAR1_INDEX; i++)
		{
			car1[i].InitObject(80 + i * (block * 4), 10+(block*8), (block * 2), 80, 0.1f, nullptr);
			Load(".\\assets\\car1.bmp", &car1[i].pBitmap);
		}
		for (int i = 0; i < CAR2_INDEX; i++)
		{
			car2[i].InitObject(80 + i * (block*5), 10 + (block * 7), 80, 80, 0.3f, nullptr);
			Load(".\\assets\\car2.bmp", &car2[i].pBitmap);
		}
		for (int i = 0; i < CAR3_INDEX; i++)
		{
			car3[i].InitObject(80 + i * (block * 4), 10 + (block * 6), (block * 3/2), 80, 0.1f, nullptr);
			Load(".\\assets\\car3.bmp", &car3[i].pBitmap);
		}
		for (int i = 0; i < CAR4_INDEX; i++)
		{
			car4[i].InitObject(80 + i * (block * 8), 10 + (block * 5), (block * 4), 80, 0.6f, nullptr);
			Load(".\\assets\\car4.bmp", &car4[i].pBitmap);
		}
	}

	void GameManager::Update()
	{
		++m_UpdateCount;

		input.UpdateMouse();
		time.UpdateTime();
		
		UpdatePlayer();
		UpdateEnemy();
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
		for (int i = 0; i < CAR1_INDEX; i++)
		{
			Upload(car1[i].pBitmap);
		}
		for (int i = 0; i < CAR2_INDEX; i++)
		{
			Upload(car2[i].pBitmap);
		}
		for (int i = 0; i < CAR3_INDEX; i++)
		{
			Upload(car3[i].pBitmap);
		}
		for (int i = 0; i < CAR4_INDEX; i++)
		{
			Upload(car4[i].pBitmap);
		}


		Upload(hBitmap_end);
		Upload(hBitmap_water);
		Upload(hBitmap_green);
		Upload(hBitmap_load);
		Upload(hBitmap_start);
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
		int playbleWidth = 800;
		int playbleheight = 800;

		render.DrawRect(10,10, 10+playbleWidth, 10+playbleheight, RGB(255, 0, 255));
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				HBITMAP setDraw=nullptr;
				switch (Map[i][j].draw)
				{
				case END:
					setDraw = hBitmap_end;
					break;
				case WATER:
					setDraw = hBitmap_water;
					break;
				case GREEN:
					setDraw = hBitmap_green;
					break;
				case LOAD:
					setDraw = hBitmap_load;
					break;
				case POSITION:
					setDraw = hBitmap_start;
					break;
				default:
					break;
				}
				/*std::string str = "draw: " + std::to_string(Map[i][j].draw);
				str += std::to_string((int)setDraw);
				render.DrawText(30 + (j * 80), 30 + (i * 80), str.c_str(), RGB(0, 255, 0));*/
				render.DrawBitmap(10+(j*80), 10+(i*80), setDraw);
			}
		}
	}

	void GameManager::DrawPlayer()
	{
		render.TransparentDrawBitmap(player.x, player.y, player.pBitmap);
	}

	void GameManager::DrawEnemy()
	{
		for (int i = 0; i < CAR1_INDEX; i++)
		{
			render.TransparentDrawBitmap(car1[i].x, car1[i].y, car1[i].pBitmap);
		}
		for (int i = 0; i < CAR2_INDEX; i++)
		{
			render.TransparentDrawBitmap(car2[i].x, car2[i].y, car2[i].pBitmap);
		}
		for (int i = 0; i < CAR3_INDEX; i++)
		{
			render.TransparentDrawBitmap(car3[i].x, car3[i].y, car3[i].pBitmap);
		}
		for (int i = 0; i < CAR4_INDEX; i++)
		{
			render.TransparentDrawBitmap(car4[i].x, car4[i].y, car4[i].pBitmap);
		}
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

	
}


