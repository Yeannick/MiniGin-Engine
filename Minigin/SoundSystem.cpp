
#include "MiniginPCH.h"
#include "SoundSystem.h"
#include "SoundClip.h"

#include <mutex>
#include <queue>
#include <stack>
// SoundSystem pimpl
class SDLSoundSystem::SDLSoundSystemImpl final
{
public:
	SDLSoundSystemImpl() = default;
	~SDLSoundSystemImpl();

	SDLSoundSystemImpl(const SDLSoundSystemImpl& other) = delete;
	SDLSoundSystemImpl(SDLSoundSystemImpl&& other) noexcept = delete;
	SDLSoundSystemImpl& operator=(const SDLSoundSystemImpl& other) = delete;
	SDLSoundSystemImpl& operator=(SDLSoundSystemImpl&& other) noexcept = delete;

	void QueueSound(const std::string & filename, int loops = 0, int volume = 100 , bool isMusic = false);
	void StopSoundQueue() { m_Active = false; };
	void SoundQueue();

private:
	bool LoadClip(SoundClip * clip);
	void PlayClip(SoundClip * clip);

	bool m_Active = true;
	std::mutex m_Mutex;
	std::queue<SoundClip*> m_pSoundQueue{};
};


// ----------------- SDL SOUND SYSTEM  Impl functions --------------------//

SDLSoundSystem::SDLSoundSystemImpl::~SDLSoundSystemImpl()
{
	// empty the SoundQueue
	for (size_t i = 0; i < m_pSoundQueue.size(); i++)
	{
		m_pSoundQueue.pop();
	}
}

void SDLSoundSystem::SDLSoundSystemImpl::QueueSound(const std::string& filename, int loops, int volume , bool isMusic)
{
	m_Mutex.lock();
	
	m_pSoundQueue.push(new SoundClip("../Data/" + filename, loops, volume , isMusic));

	m_Mutex.unlock();
}

void SDLSoundSystem::SDLSoundSystemImpl::SoundQueue()
{
	std::vector<SoundClip*> soundClips;
	while (m_Active)
	{
		if (m_pSoundQueue.empty())
		{
			return;
		}
		else
		{
			m_Mutex.lock();
			soundClips.push_back(m_pSoundQueue.front());
			m_pSoundQueue.pop();
			m_Mutex.unlock();

			if (LoadClip(soundClips.front()))
			{
				PlayClip(soundClips.front());
			}
		}
		if (!soundClips.empty())
		{
			for (size_t i = 0; i < soundClips.size(); i++)
			{
				if (soundClips[i]->IsPlaying())
				{
					continue;
				}
				delete soundClips[i];
				soundClips[i] = nullptr;
				soundClips.erase(soundClips.begin() + i);
			}
		}
	}
	if (!soundClips.empty())
	{
		for (size_t i = 0; i < soundClips.size(); i++)
		{
			delete soundClips[i];
			soundClips[i] = nullptr;
		}
	}
	
}

bool SDLSoundSystem::SDLSoundSystemImpl::LoadClip(SoundClip* clip)
{
	return clip->LoadSound();
}

void SDLSoundSystem::SDLSoundSystemImpl::PlayClip(SoundClip* clip)
{
	clip->Play();
}

// ----------------- SDL SOUND SYSTEM   --------------------//

SDLSoundSystem::SDLSoundSystem() :
	m_pImpl(new SDLSoundSystemImpl())
{
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096); // you might use MIX_DEFAULT_FREQUENCY(22050) since that is a good value for most games. // From documentation on SDL_Mixer , 2 channels for stereo
	m_Thread = std::thread(&SDLSoundSystem::ThreadUpdate, this);
}

SDLSoundSystem::~SDLSoundSystem()
{
	m_Thread.join();
	Mix_CloseAudio();

	delete m_pImpl;
	m_pImpl = nullptr;
}

void SDLSoundSystem::ThreadUpdate()
{
	while (m_KeepThreadAlive)
	{
		SoundQueue();
	}
}

// ----------------- SDL SOUND SYSTEM Calling Impl functions --------------------//
void SDLSoundSystem::SoundQueue()
{
	m_pImpl->SoundQueue();
}

void SDLSoundSystem::StopSoundQueue()
{
	m_pImpl->StopSoundQueue();
}
void SDLSoundSystem::QueueSound(const std::string& fileName, int loops, int volume ,bool isMusic)
{
	m_pImpl->QueueSound(fileName, loops, volume , isMusic);
}
