#include "AudioHandler.h"
#include "Engine/Audio/AudioUtils.h"
#include "Log.h"

namespace SpaceInvaders
{
    AudioHandler::AudioHandler(std::wstring device)
        : m_Volume(0.01), m_CurrentTime(0.0)
    {
        m_StreamParams = new AudioEngine::StreamParameters;
        m_Stream = new AudioEngine::AudioStream<short>();
        m_State = new AudioEngine::AudioState();

        m_State->AddClip(AudioEngine::AudioClip("BgNote_0", 
            [this](double time, double ts)
            {
                double frequency = 51.91;
                double sig = sin(frequency * 2.0 * AudioEngine::AudioUtils::PI * std::fmod(time, 1.0));
                return sig;
            },
            70, true));
        m_State->AddClip(AudioEngine::AudioClip("BgNote_1", 
            [this](double time, double ts)
            {
                double frequency = 49.0;
                return sin(frequency * 2.0 * AudioEngine::AudioUtils::PI * std::fmod(time, 1.0));
            },
            70, true));
        m_State->AddClip(AudioEngine::AudioClip("BgNote_2",
            [this](double time, double ts)
            {
                double frequency = 46.25;
                return sin(frequency * 2.0 * AudioEngine::AudioUtils::PI * std::fmod(time, 1.0));
            },
            70, true));
        m_State->AddClip(AudioEngine::AudioClip("BgNote_3",
            [this](double time, double ts)
            {
                double frequency = 61.74;
                return sin(frequency * 2.0 * AudioEngine::AudioUtils::PI * std::fmod(time, 1.0));
            },
            70, true));
        m_State->AddClip(AudioEngine::AudioClip("AlienShip",
            [this](double time, double ts)
            {
                double oscFreq = 8.0;
                double freq = 784.0 + 46.0 * cos(oscFreq * 2.0 * AudioEngine::AudioUtils::PI * time);
                return sin(freq * 2.0 * AudioEngine::AudioUtils::PI * std::fmod(time, 1.0 / oscFreq));
            },
            20000, true));

        m_StreamParams->outputDevice = device;
        m_Stream->Create(*m_StreamParams);

        m_Stream->SetUserFunction([this](double time, double ts) 
            {
                m_CurrentTime = time;
                double output = 0.0;
                for (AudioEngine::AudioClip* clip : m_CurrentClips)
                {
                    double sample = clip->AudioFunction(time - clip->StartTime, ts);
                    if (clip->IsSquareWave) sample = AudioEngine::AudioUtils::ToSquareWave(sample);
                    output += sample;
                }
                if (m_CurrentClips.size() > 0) output /= m_CurrentClips.size();
                return output * m_Volume;
            });
    }

    AudioHandler::~AudioHandler()
    {
        delete m_Stream;
        delete m_State;
        delete m_StreamParams;
    }

    void AudioHandler::PlayClip(std::string clipName)
    {
        AudioEngine::AudioClip* clip = m_State->GetClip(clipName);
        if (clip != nullptr)
        {
            clip->DurationLeft = clip->Duration;
            clip->StartTime = m_CurrentTime;
            m_CurrentClips.push_back(clip);
        }
    }

    void AudioHandler::StopClip(std::string clipName)
    {
        AudioEngine::AudioClip* clip = m_State->GetClip(clipName);
        if (clip != nullptr)
            clip->DurationLeft = 0.0;
    }

    bool AudioHandler::IsClipActive(std::string clipName)
    {
        return std::find(m_CurrentClipList.begin(), m_CurrentClipList.end(), clipName) != m_CurrentClipList.end();
    }

    void AudioHandler::OnUpdate(float ts)
    {
        for (AudioEngine::AudioClip* clip : m_CurrentClips)
            clip->DurationLeft -= ts * 1000;

        m_CurrentClips.erase(
            std::remove_if(
                m_CurrentClips.begin(),
                m_CurrentClips.end(),
                [](AudioEngine::AudioClip* clip) { return clip->DurationLeft <= 0.0; }
            ),
            m_CurrentClips.end()
        );

        m_CurrentClipList.clear();
        for (auto* clip : m_CurrentClips)
            m_CurrentClipList.push_back(clip->Name);
    }

    double AudioHandler::WindowFunction(double duration, double durationLeft)
    {
        double windowCutoff = 0.1;
        if (durationLeft >= duration - windowCutoff * duration)
            return (duration - durationLeft) / (duration * windowCutoff);
        else if (durationLeft <= duration * windowCutoff)
            return durationLeft / (duration * windowCutoff);
        else
            return 1.0;
        //double freq = 1.0 / (2.0 * duration);
        //return sin(freq * 2.0 * AudioEngine::AudioUtils::PI * (duration - durationLeft));
    }
}
