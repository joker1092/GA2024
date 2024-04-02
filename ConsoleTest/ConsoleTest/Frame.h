#pragma once
#include <Windows.h>
#include "Time.h"
#include "ConsoleRenderer.h"

namespace Frame {
	void Init();
	int ProcessInput();
	void FixedUpdate();
	void Update();
	void Render();
	void Quit();
}