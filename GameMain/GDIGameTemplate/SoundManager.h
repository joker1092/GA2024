#pragma once
#include <iostream>
#include <vector>
#include "fmod.hpp"
#include <conio.h>
#include <vector>

using namespace std;
using namespace FMOD;

namespace mySound
{
	void InitFMOD();

	void LoadSounds();

	void PlaySounds(int index);

	void ReleaseSounds();


}

