#include "SoundManager.h"
#define MAX_SOUNDS 10						// 최대 크기


FMOD::System* soundsystem(nullptr);
FMOD::Sound* sounds[MAX_SOUNDS];			// 사운드 배열
FMOD::Channel* channels[MAX_SOUNDS];		// 채널 배열

//std::vector<FMOD::Sound*> sounds;
//std::vector<FMOD::Channel*> channels;

namespace mySound
{
	// 초기화
	void InitFMOD()										
	{
		FMOD::System_Create(&soundsystem);								
		soundsystem->init(MAX_SOUNDS, FMOD_INIT_NORMAL, nullptr);
	}

	// 사운드 로드 (기본형태) 일일히 사운드파일이름을 넣어줘야함. samplefile은 예시
	void LoadSounds()
	{
		for (int i = 0; i < MAX_SOUNDS; i++)
		{
			soundsystem->createSound("drumloop.wav", FMOD_DEFAULT, nullptr, &sounds[i]);
		}
	}

	// 사운드 재생
	void PlaySounds(int index)
	{
		if (index >= 0 && index <= MAX_SOUNDS)
		{
			soundsystem->playSound(sounds[index], nullptr, false, &channels[index]);
		}
	}

	// 사운드 해제
	void ReleaseSounds()
	{
		for (int i = 0; i < MAX_SOUNDS; i++)
		{
			if (sounds[i])
			{
				sounds[i]->release();
			}
			if (channels[i])
			{
				channels[i]->stop();
			}
		}
		soundsystem->close();
		soundsystem->release();
	}
}

