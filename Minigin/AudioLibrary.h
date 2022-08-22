#pragma once
#include "Singleton.h"
#include <vector>
#include "SoundClip.h"
class AudioLibrary : public Singleton<AudioLibrary>
{
public:

	const SoundClip* GetAudioClip(unsigned int id);
	void  AddAudioClip(SoundClip* clip);
private:
	std::vector<SoundClip*> m_Clips;
};