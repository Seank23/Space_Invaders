#include "AudioState.h"

namespace AudioEngine
{
    AudioState::AudioState()
    {

    }

    AudioState::~AudioState()
    {

    }

    AudioClip* AudioState::GetClip(std::string name)
    {
        for (AudioClip& clip : m_Clips)
        {
            if (clip.Name == name)
                return &clip;
        }
        return nullptr;
    }
}
