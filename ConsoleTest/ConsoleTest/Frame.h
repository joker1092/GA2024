#pragma once
#include <Windows.h>
#include "Time.h"
#include "ConsoleRenderer.h"
#include "player.h"
#include "Map.h"
#include "InputSystem.h"

#include <iostream>

namespace Frame {
	extern bool g_bQuit;

	void Init();
	void ProcessInput();
	void FixedUpdate();
	void Update();
	void Render();
	void Quit();

	void setTimer(char* str);
	bool isClear();
}