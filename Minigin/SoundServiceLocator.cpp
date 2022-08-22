#include "MiniginPCH.h"
#include "SoundServiceLocator.h"

NullSoundSystem SoundServiceLocator::m_pDefaultSoundSystem;
SoundSystem* SoundServiceLocator::m_pSoundInstance = &m_pDefaultSoundSystem;

SoundSystem& SoundServiceLocator::GetSoundSystem()
{
	return *m_pSoundInstance;
}

void SoundServiceLocator::RegisterSoundSystem(SoundSystem* soundSys)
{

	if (m_pSoundInstance != &m_pDefaultSoundSystem)
	{
		delete m_pSoundInstance;
	}

	m_pSoundInstance = (soundSys == nullptr ? &m_pDefaultSoundSystem : soundSys);
}

void SoundServiceLocator::FreeSoundSystem()
{
	delete m_pSoundInstance;
	m_pSoundInstance = nullptr;
}
