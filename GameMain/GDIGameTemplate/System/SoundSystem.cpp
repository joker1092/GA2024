#include "SoundSystem.h"

namespace mySound
{

	SoundManager* SoundManager::mInstance = nullptr;
	SoundManager* soundManger = SoundManager::GetInstance();		// 초기화

	SoundManager* SoundManager::GetInstance()
	{
		if (mInstance == nullptr)
		{
			mInstance = new SoundManager();
			
		}
		return mInstance;
	}

	void SoundManager::DestroyInstance()
	{
		delete mInstance;
		mInstance = nullptr;
	}

	void SoundManager::LoadSounds(SoundList list, bool loopCheck, const char* music)
	{
		System_Create(&mSystem);
		mSystem->init(3, FMOD_INIT_NORMAL, 0);			// 최대 3개 채널 동시에 재생 가능

		if (loopCheck == true)
		{
			mSystem->createSound(music, FMOD_LOOP_NORMAL, 0, &mSoundList[static_cast<int>(list)]);
		}
		else
		{
			mSystem->createSound(music, FMOD_LOOP_OFF, 0, &mSoundList[static_cast<int>(list)]);
		}
	}

	void SoundManager::PlaySounds(SoundList list, SoundChannel channel)
	{
		mChannel[static_cast<int>(channel)]->stop();
		mSystem->playSound(mSoundList[static_cast<int>(list)], NULL, 0, &mChannel[static_cast<int>(channel)]);
		mChannel[static_cast<int>(channel)]->setVolume(mVolume);
	}

	void SoundManager::StopSounds(SoundChannel channel)
	{
		mChannel[static_cast<int>(channel)]->stop();
	}

	void SoundManager::SetVolume(float volume)
	{
		mVolume = volume;
		for (unsigned int i = 0; i < static_cast<unsigned int>(SoundChannel::Size); i++)
		{
			mChannel[i]->setVolume(mVolume);
		}
	}

	void SoundManager::RelaseSounds()
	{
		mSystem->release();
		mSystem->close();
	}

	SoundManager::SoundManager() :mSystem(), mChannel{}, mSoundList{}, mVolume(0.5f)
	{
	}

	SoundManager::~SoundManager()
	{
	}



}

