#pragma once
#include "SoundSystem.h"

class SoundServiceLocator final
{
public :
	static SoundSystem& GetSoundSystem();
	static void RegisterSoundSystem(SoundSystem* soundSys);
	static void FreeSoundSystem();


	SoundServiceLocator() = delete;
	~SoundServiceLocator() = delete;
	SoundServiceLocator(const SoundServiceLocator&) = delete;
	SoundServiceLocator& operator=(const SoundServiceLocator&) = delete;
	SoundServiceLocator(SoundServiceLocator&&) = delete;
	SoundServiceLocator& operator=(SoundServiceLocator&&) = delete;

private:
	static SoundSystem* m_pSoundInstance;
	static NullSoundSystem m_pDefaultSoundSystem;
};