#include "AudioHandler.h"
#include "Engine/Audio/AudioUtils.h"
#include "Log.h"

#include <ctime>

namespace SpaceInvaders
{
    AudioHandler::AudioHandler(std::wstring device)
        : m_Volume(0.01), m_CurrentTime(0.0), m_Seed(std::time(0))
    {
        m_StreamParams = new AudioEngine::StreamParameters;
        m_Stream = new AudioEngine::AudioStream<short>();
        m_State = new AudioEngine::AudioState();

        m_State->AddClip(AudioEngine::AudioClip("BgNote_0", 
            [this](double time)
            {
                double frequency = 51.91;
                return sin(frequency * 2.0 * AudioEngine::AudioUtils::PI * std::fmod(time, 1.0));
            },
            70, true, 2.0));
        m_State->AddClip(AudioEngine::AudioClip("BgNote_1", 
            [this](double time)
            {
                double frequency = 49.0;
                return sin(frequency * 2.0 * AudioEngine::AudioUtils::PI * std::fmod(time, 1.0));
            },
            70, true, 2.0));
        m_State->AddClip(AudioEngine::AudioClip("BgNote_2",
            [this](double time)
            {
                double frequency = 46.25;
                return sin(frequency * 2.0 * AudioEngine::AudioUtils::PI * std::fmod(time, 1.0));
            },
            70, true, 2.0));
        m_State->AddClip(AudioEngine::AudioClip("BgNote_3",
            [this](double time)
            {
                double frequency = 61.74;
                return sin(frequency * 2.0 * AudioEngine::AudioUtils::PI * std::fmod(time, 1.0));
            },
            70, true, 2.0));
        m_State->AddClip(AudioEngine::AudioClip("AlienShip",
            [this](double time)
            {
                double oscFreq = 8.0;
                double freq = 784.0 + 46.0 * cos(oscFreq * 2.0 * AudioEngine::AudioUtils::PI * time);
                return 0.5 * sin(freq * 2.0 * AudioEngine::AudioUtils::PI * std::fmod(time, 1.0 / oscFreq));
            },
            20000, true, 0.8));
        m_State->AddClip(AudioEngine::AudioClip("PlayerShoot",
            [this](double time)
            {
                double noise = AudioEngine::AudioUtils::GetNoiseSample(m_Seed) / 2.0;
                double frequency = 2349.32 * cos(0.05 * AudioEngine::AudioUtils::PI * time);
                double sig = sin(frequency * 2.0 * AudioEngine::AudioUtils::PI * std::fmod(time, 1.0));
                return sig + noise;
            },
            700, true, 0.5));
        m_State->AddClip(AudioEngine::AudioClip("AlienHit",
            [this](double time)
            {
                double noise = AudioEngine::AudioUtils::GetNoiseSample(m_Seed) / 2.0;
                double frequency;
                if (time < 0.075)
                    frequency = 740.0 * cos(1.5 * 2.0 * AudioEngine::AudioUtils::PI * time);
                else if (time < 0.15)
                    frequency = 1110.0 * cos(1.5 * 2.0 * AudioEngine::AudioUtils::PI * (time - 0.075));
                else if (time < 0.225)
                    frequency = 1110.0 * cos(1.5 * 2.0 * AudioEngine::AudioUtils::PI * (time - 0.15));
                else
                    frequency = 1110.0 * cos(1.5 * 2.0 * AudioEngine::AudioUtils::PI * (time - 0.225));
                double sig = sin(frequency * 2.0 * AudioEngine::AudioUtils::PI * std::fmod(time, 1.0));
                return sig;
            },
            300, true, 0.9));
        m_State->AddClip(AudioEngine::AudioClip("PlayerHit",
            [this](double time)
            {
                double noise = (4.0 / (1.0 + 8.0 * time)) * AudioEngine::AudioUtils::GetNoiseSample(m_Seed);
                double frequency = 82.41;
                double sig = sin(frequency * 2.0 * AudioEngine::AudioUtils::PI * std::fmod(time, 1.0));
                return 0.5 * sig + noise;
            },
            700, false, 1.0));

        m_StreamParams->outputDevice = device;
        m_Stream->Create(*m_StreamParams);

        m_Stream->SetUserFunction([this](double time) 
            {
                m_CurrentTime = time;
                double output = 0.0;
                for (AudioEngine::AudioClip* clip : m_CurrentClips)
                {
                    double sample = clip->AudioFunction(time - clip->StartTime);
                    if (clip->IsSquareWave) sample = AudioEngine::AudioUtils::ToSquareWave(sample);
                    output += sample * clip->Volume;
                }
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
        StopClip(clipName);
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

    void AudioHandler::StopAll()
    {
        for (AudioEngine::AudioClip* clip : m_CurrentClips)
        {
            clip->DurationLeft = 0.0;
        }
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
}
