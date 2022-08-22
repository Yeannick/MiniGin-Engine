#pragma once
#include <string>
#include "SDL_mixer.h"


class SoundClip final
{
public:
	explicit SoundClip(const std::string& path , int loops , int volume , bool isMusic = false);
	explicit SoundClip(const std::string& path , int loops );
	~SoundClip();

	SoundClip(const SoundClip& other) = delete;
	SoundClip(SoundClip&& other) = delete;
	SoundClip& operator=(const SoundClip& other) = delete;
	SoundClip& operator=(SoundClip&& other) noexcept = delete;
	bool operator==(const SoundClip&) const;

	bool LoadSound();

	void Play();
	void Pause() const;
	void Resume() const;

	void SetVolume(const int volume);

	bool IsPlaying() const;
private:
	// SoundClip INFO
	std::string m_Path;
	int m_Volume;
	int m_Loops;
	bool m_IsMusic = false;
	//--- SDL_MIXER ---// 
	int m_Channel;
	Mix_Chunk* m_pSample = nullptr;
	Mix_Music* m_pMusicSample = nullptr;
};

