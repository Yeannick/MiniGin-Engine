#include "MiniginPCH.h"

#include "SoundClip.h"

SoundClip::SoundClip(const std::string& path, int loops, int volume , bool isMusic):
	m_Path(path),
	m_Volume(volume),
	m_Loops(loops),
	m_IsMusic(isMusic)
{
	SetVolume(volume);
}

SoundClip::SoundClip(const std::string& path, int loops):
	m_Path(path),
	m_Volume(50),
	m_Loops(loops)
{
	SetVolume(m_Volume);
}

SoundClip::~SoundClip()
{
	if (!m_IsMusic)
	{
		Mix_FreeChunk(m_pSample);
		m_pSample = nullptr;
		std::cout << "AudioClip Removed" << std::endl;
	}
	else
	{
		Mix_FreeMusic(m_pMusicSample);
		m_pSample = nullptr;
	}

}

bool SoundClip::operator==(const SoundClip& A) const
{
	return A.m_Loops == m_Loops && A.m_Volume == m_Volume && A.m_Path == m_Path;
}

bool SoundClip::LoadSound()
{
	if (m_IsMusic)
	{
		m_pMusicSample = Mix_LoadMUS(m_Path.c_str());
		SetVolume(m_Volume);
		if (m_pMusicSample)
			return true;

		printf("Mix_LoadMUS: %s\n", Mix_GetError());
		return false;
	}
	else
	{
		m_pSample = Mix_LoadWAV(m_Path.c_str());
		if (m_pSample)
			return true;

		printf("Mix_LoadWAV: %s\n", Mix_GetError());
		return false;
	}
	

	/*Mix_Chunk* sound = NULL;

	sound = Mix_LoadWAV("sound.wav"); if (sound == NULL) { fprintf(stderr, "Unable to load WAV file: %s\n", Mix_GetError()); }*/
}

void SoundClip::Play()
{
	if (m_IsMusic)
	{
		m_Channel = Mix_PlayMusic(m_pMusicSample, m_Loops);
		if (m_Channel == -1)
		{
			printf("Mix_PlayMusic: %s\n", Mix_GetError());
		}
	}
	//https://extranet.jcesar.casa/W3/SDL/SDL_mixer/SDL_mixer_28.html#SEC28
	m_Channel = Mix_PlayChannel(-1, m_pSample, m_Loops);
	if (m_Channel == -1)
	{
		printf("Mix_PlayChannel: %s\n", Mix_GetError());
	}

}

void SoundClip::Pause() const
{
	if (m_IsMusic)
	{
		if (m_Channel != -1)
		{
			Mix_PauseMusic();
		}
	}
	else
	{
		if (m_Channel != -1)
		{
			Mix_Pause(m_Channel);
		}
	}
	
}

void SoundClip::Resume() const
{
	if (m_IsMusic)
	{
		if (m_Channel != -1)
		{
			Mix_ResumeMusic();
		}
	}
	else
	{
		if (m_Channel != -1)
		{
			Mix_Resume(m_Channel);
		}
	}
	
}

void SoundClip::SetVolume(const int volume)
{
	if (m_IsMusic)
	{
		m_Volume = Mix_VolumeMusic(volume);
	}
	//https://wiki.libsdl.org/SDL_mixer/Mix_VolumeChunk
	else
	{
		if (m_pSample)
		{
			m_Volume = Mix_VolumeChunk(m_pSample, volume);
			printf("Volume set to: %d\n", m_Volume);
		}
	}
}

bool SoundClip::IsPlaying() const
{
	if (m_IsMusic)
	{
		return Mix_PlayingMusic() == 1;
	}
	else
	{
		return Mix_Playing(m_Channel) == 1;
	}
	
	// https://wiki.libsdl.org/SDL_mixer/Mix_Playing
	//If the channel is currently playing, this function returns 1. Otherwise it returns 0.
	//If the specified channel is - 1, all channels are checked, and this function returns the number of channels currently playing.
}
