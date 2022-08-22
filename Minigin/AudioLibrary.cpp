#include "MiniginPCH.h"
#include "AudioLibrary.h"

const SoundClip* AudioLibrary::GetAudioClip(unsigned int id)
{
    return m_Clips[id];
}

void AudioLibrary::AddAudioClip(SoundClip* clip)
{
    m_Clips.push_back(clip);
}
