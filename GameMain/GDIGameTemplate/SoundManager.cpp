#include "SoundManager.h"
#define MAX_SOUNDS 10						// �ִ� ũ��


FMOD::System* soundsystem(nullptr);
FMOD::Sound* sounds[MAX_SOUNDS];			// ���� �迭
FMOD::Channel* channels[MAX_SOUNDS];		// ä�� �迭

//std::vector<FMOD::Sound*> sounds;
//std::vector<FMOD::Channel*> channels;

namespace mySound
{
	// �ʱ�ȭ
	void InitFMOD()										
	{
		FMOD::System_Create(&soundsystem);								
		soundsystem->init(MAX_SOUNDS, FMOD_INIT_NORMAL, nullptr);
	}

	// ���� �ε� (�⺻����) ������ ���������̸��� �־������. samplefile�� ����
	void LoadSounds()
	{
		for (int i = 0; i < MAX_SOUNDS; i++)
		{
			soundsystem->createSound("drumloop.wav", FMOD_DEFAULT, nullptr, &sounds[i]);
		}
	}

	// ���� ���
	void PlaySounds(int index)
	{
		if (index >= 0 && index <= MAX_SOUNDS)
		{
			soundsystem->playSound(sounds[index], nullptr, false, &channels[index]);
		}
	}

	// ���� ����
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

