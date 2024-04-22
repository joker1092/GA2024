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
	DEATH,
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
const int CAR3_INDEX = 3;
const int CAR4_INDEX = 2;

const int WOOD1_INDEX = 2;
const int WOOD2_INDEX = 3;
const int WOOD3_INDEX = 2;

const int block = 80;

namespace game {

	TimeSystem time;
	InputSystem input;
	RenderSystem render;
	Object player;
	int playerLife = 3;
	int playerInitX = 410, playerInitY = 730;
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

	HBITMAP hBitmap_death = nullptr;

	struct bound {
		int x;
		int y;
		BackDraw draw;
	};

	bound Map[10][10];

	state gameState = READY;

	bool preCollison = false;
	bool curCollison = false;

	bool Clamp(int x, int y) {
		int offsetx = 10;
		int offsety = 10;
		int playbleWidth = 800-block;
		int playbleheight = 800 - block;

		return (x<offsetx || y<offsety || x>(offsetx + playbleWidth) || y>(offsety + playbleheight));
	}


	void ObjectsRender(Object obj[], int len) {
		for (int i = 0; i < len; i++)
		{
			render.TransparentDrawBitmap(obj[i].x, obj[i].y, obj[i].pBitmap);
		}
	}


	//충돌 확인
	bool isRectEnter(Object* obj1, Object* obj2) {
		return !((obj1->x) > (obj2->x + obj2->width) || (obj1->x + obj1->width) < (obj2->x) || (obj1->y) > (obj2->y + obj2->height) || (obj1->y + obj1->height) > (obj2->y + obj2->height));
	}


	void UpdatePlayer()
	{
		//if (gameState!=DEATH)
		//{
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
					player.SetPos(player.x, player.y + block);
				}
			}
			else if (input.IsKeyDown('S'))
			{
				player.Move(0, block);
				if (Clamp(player.x, player.y)) {
					player.SetPos(player.x, player.y - block);
				}
			}
		//}
	}

	void UpdateEnemy()
	{
		//car object
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

		//wood object
		for (int i = 0; i < WOOD1_INDEX; i++)
		{
			
			wood1[i].Move(-wood1[i].speed, 0);
			if (wood1[i].x + (5*block) < 10)
			{
				wood1[i].SetPos(800, wood1->y);
			}
		}
		for (int i = 0; i < WOOD2_INDEX; i++)
		{
			wood2[i].Move(wood2[i].speed, 0);
			if (wood2[i].x > 800)
			{
				wood2[i].SetPos(-160, wood2->y);
			}
		}
		for (int i = 0; i < WOOD3_INDEX; i++)
		{
			wood3[i].Move(-wood3[i].speed, 0);
			if (wood3[i].x + 160 < 10)
			{
				wood3[i].SetPos(800, wood3->y);
			}
		}
	}

	void UpdateState() {

		if (gameState==DEATH)
		{
			if (playerLife>0)
			{
				player.SetPos(410, 730);
				gameState = START;
			}
		}


		if (player.y<block)
		{

		}
		else if (player.y < wood3->y + block) {
			for (int i = 0; i < WOOD3_INDEX; i++)
			{
				if (!isRectEnter(&player, &wood3[i]))
				{
					gameState = DEATH;
				}

			}
		}
		else if (player.y < wood2->y + block) {
			for (int i = 0; i < WOOD2_INDEX; i++)
			{
				if (!isRectEnter(&player, &wood2[i]))
				{
					gameState = DEATH;
				}

			}
		}
		else if (player.y < wood1->y+block)
		{
			for (int i = 0; i < WOOD1_INDEX; i++)
			{
				if (!isRectEnter(&player, &wood1[i]))
				{
					gameState = DEATH;
				}

			}
		}
		else if (player.y < car4->y) {
			gameState = START;
		}
		else if (player.y < car4->y+block ) {
			for (int i = 0; i < CAR4_INDEX; i++)
			{
				if (isRectEnter(&player, &car4[i]))
				{
					gameState = DEATH;
				}
				
			}
		}
		else if (player.y < car3->y + block) {
			for (int i = 0; i < CAR3_INDEX; i++)
			{
				if (isRectEnter(&player, &car3[i]))
				{
					gameState = DEATH;
				}
				
			}
		}
		else if (player.y < car2->y + block) {
			for (int i = 0; i < CAR2_INDEX; i++)
			{
				if (isRectEnter(&player, &car2[i]))
				{
					gameState = DEATH;
				}
				
			}
		}
		else if (player.y < car1->y + block)
		{
			for (int i = 0; i < CAR1_INDEX; i++) {
				if (isRectEnter(&player, &car1[i]))
				{
					gameState = DEATH;
				}
			}			
		}
		else {
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

		Load(".\\assets\\death.bmp", &hBitmap_death);
		player.InitObject(410, 730, 80, 80, 0.3f, nullptr);
		Load(".\\assets\\frog_up.bmp", &player.pBitmap);
		//car object
		for (int i = 0; i < CAR1_INDEX; i++)
		{
			car1[i].InitObject(80 + i * (block * 4), 10+(block*8), (block * 2), 80, 0.1f, nullptr);
			Load(".\\assets\\car1.bmp", &car1[i].pBitmap);
		}
		for (int i = 0; i < CAR2_INDEX; i++)
		{
			car2[i].InitObject(80 + i * (block*5), 10 + (block * 7), block, 80, 0.3f, nullptr);
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
		//wood object
		for (int i = 0; i < WOOD1_INDEX; i++)
		{
			wood1[i].InitObject(80 + i * (block * 7), 10 + (block * 3), (block * 5), 80, 0.3f, nullptr);
			Load(".\\assets\\wood1.bmp", &wood1[i].pBitmap);
		}
		for (int i = 0; i < WOOD2_INDEX; i++)
		{
			wood2[i].InitObject(80 + i * (block * 4), 10 + (block * 2), (block * 3 / 2), 80, 0.1f, nullptr);
			Load(".\\assets\\wood2.bmp", &wood2[i].pBitmap);
		}
		for (int i = 0; i < WOOD3_INDEX; i++)
		{
			wood3[i].InitObject(80 + i * (block * 8), 10 + (block * 1), (block * 4), 80, 0.6f, nullptr);
			Load(".\\assets\\wood3.bmp", &wood3[i].pBitmap);
		}

	}

	void GameManager::Update()
	{
		++m_UpdateCount;

		input.UpdateMouse();
		time.UpdateTime();
		
		if (gameState!=DEATH)
		{
			UpdatePlayer();
			UpdateEnemy();
		}
		
		//UpdateBlueCircle();
		UpdateState();

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
		DrawEnemy();
		DrawPlayer();
		

		render.EndDraw();
	}
	void GameManager::Finalize()
	{

		Upload(player.pBitmap);
		/*Upload(enemy.pBitmap);
		Upload(hTestBitmap);*/

		//car object
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

		//wood object
		for (int i = 0; i < WOOD1_INDEX; i++)
		{
			Upload(wood1[i].pBitmap);
		}
		for (int i = 0; i < WOOD2_INDEX; i++)
		{
			Upload(wood2[i].pBitmap);
		}
		for (int i = 0; i < WOOD3_INDEX; i++)
		{
			Upload(wood3[i].pBitmap);
		}


		Upload(hBitmap_end);
		Upload(hBitmap_water);
		Upload(hBitmap_green);
		Upload(hBitmap_load);
		Upload(hBitmap_start);
		Upload(hBitmap_death);

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
		if (gameState == DEATH)
		{
			render.TransparentDrawBitmap(player.x, player.y, hBitmap_death);
		}
	}

	void GameManager::DrawEnemy()
	{
		
		//car object
		ObjectsRender(car1, CAR1_INDEX);
		ObjectsRender(car2, CAR2_INDEX);
		ObjectsRender(car3, CAR3_INDEX);
		ObjectsRender(car4, CAR4_INDEX);

		//wood object
		ObjectsRender(wood1, WOOD1_INDEX);
		ObjectsRender(wood2, WOOD2_INDEX);
		ObjectsRender(wood3, WOOD3_INDEX);

		
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
		std::string str = "gameState: " + std::to_string(gameState);
		str += "           player.y " + std::to_string(player.y);
		str += "           wood1[0].y " + std::to_string(wood1[0].y);
		str += "           isRectEnter " + isRectEnter(&player, &car1[0]);
		str += "           isRectEnter " + isRectEnter(&player, &car1[1]);
		str += "           isRectEnter " + isRectEnter(&player, &car1[2]);

		render.DrawText(40, 40, str.c_str(), RGB(255, 0, 0));

	}
	void GameManager::Load(const char* path, HBITMAP* bitmap) {
		//const char* path = ".\\assets\\sample.bmp";
		*bitmap = render.LoadImdage(path);
	}
	void GameManager::Upload(HBITMAP bitmap) {
		render.ReleaseImage(bitmap);
	}
	
	
	

}


