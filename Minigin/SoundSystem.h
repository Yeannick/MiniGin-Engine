#pragma once

#include <string>
#include <thread>

class SoundSystem
{
public:
	SoundSystem() = default;
	virtual ~SoundSystem() = default;

	SoundSystem(const SoundSystem & other) = delete;
	SoundSystem(SoundSystem && other) noexcept = delete;
	SoundSystem& operator=(const SoundSystem & other) = delete;
	SoundSystem& operator=(SoundSystem && other) noexcept = delete;


	virtual void QueueSound(const std::string& fileName , int loops = 0 , int volume = 100, bool isMusic = false) = 0;
	virtual void QueueSound(const std::string& fileName , int volume) = 0;

	virtual void SoundQueue() = 0;
	virtual void StopSoundQueue() = 0;
};

class SDLSoundSystem final : public SoundSystem
{
public:
	SDLSoundSystem();
	~SDLSoundSystem() override;

	SDLSoundSystem(const SDLSoundSystem& other) = delete;
	SDLSoundSystem(SDLSoundSystem&& other) noexcept = delete;
	SDLSoundSystem& operator=(const SDLSoundSystem& other) = delete;
	SDLSoundSystem& operator=(SDLSoundSystem&& other) noexcept = delete;

	void QueueSound(const std::string& fileName, int loops = 0, int volume = 100 , bool isMusic = false) override;
	void QueueSound(const std::string& fileName, int volume) override 
	{
		QueueSound(fileName, 0, volume);
	} 
	void ThreadUpdate();
	void SoundQueue() override;
	void StopSoundQueue() override;

private:
	std::thread m_Thread;
	bool m_KeepThreadAlive = true;
	class SDLSoundSystemImpl;
	SDLSoundSystemImpl* m_pImpl{ nullptr };
};

// Need null version in case Other cant be fetched
class NullSoundSystem final : public SoundSystem
{
public:
	NullSoundSystem() = default;
	~NullSoundSystem() override = default;

	NullSoundSystem(const NullSoundSystem& other) = delete;
	NullSoundSystem(NullSoundSystem&& other) noexcept = delete;
	NullSoundSystem& operator=(const NullSoundSystem& other) = delete;
	NullSoundSystem& operator=(NullSoundSystem&& other) noexcept = delete;

	void QueueSound(const std::string& , int  = 0, int  = 100 , bool = false) override {};
	void QueueSound(const std::string& , int ) override {};


	void SoundQueue() override {};
	void StopSoundQueue() override {};

};