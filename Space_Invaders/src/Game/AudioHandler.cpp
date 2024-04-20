#include "AudioHandler.h"
#include "Engine/Audio/AudioUtils.h"
#include "Log.h"

namespace SpaceInvaders
{
    double GetSample(AudioEngine::AudioClip* clip, float volume, double time, double ts)
    {
        if (clip == nullptr || clip->DurationLeft <= 0)
            return 0.0;

        double pi = AudioEngine::AudioUtils::PI;
        //double oscFreq = 1.0;
        //double freq = 220.0 + 50.0 * cos(oscFreq * 2.0 * pi * time);
        //double sample = sin(freq * 2.0 * pi * std::fmod(time, 1.0 / oscFreq));
        //double squareOutput = sample > 0.0 ? 1.0 : -1.0;
        clip->DurationLeft -= ts * 1000;
        double output = 0.0;
        output = sin(clip->Frequencies[0] * 2.0 * pi * std::fmod(time, 1.0));
        if (clip->IsSquareWave) output = AudioEngine::AudioUtils::ToSquareWave(output);
        return output * volume;
    }

    AudioHandler::AudioHandler(std::wstring device)
        : m_CurrentClip(nullptr), m_Volume(0.1)
    {
        m_StreamParams = new AudioEngine::StreamParameters;
        m_Stream = new AudioEngine::AudioStream<short>();
        m_State = new AudioEngine::AudioState();

        m_State->AddClip(AudioEngine::AudioClip("BgNote_0", { 51.91 }, { -1 }, { 0 }, 70, true));
        m_State->AddClip(AudioEngine::AudioClip("BgNote_1", { 49.0 }, { -1 }, { 0 }, 70, true));
        m_State->AddClip(AudioEngine::AudioClip("BgNote_2", { 46.25 }, { -1 }, { 0 }, 70, true));
        m_State->AddClip(AudioEngine::AudioClip("BgNote_3", { 61.74 }, { -1 }, { 0 }, 70, true));

        m_StreamParams->outputDevice = device;
        m_Stream->Create(*m_StreamParams);
        m_Stream->SetUserFunction([this](double time, double ts) { return GetSample(m_CurrentClip, m_Volume, time, ts); });
    }

    AudioHandler::~AudioHandler()
    {
        delete m_Stream;
        delete m_State;
        delete m_StreamParams;
    }

    void AudioHandler::PlayClip(std::string clipName)
    {
        m_CurrentClip = m_State->GetClip(clipName);
        if (m_CurrentClip)
            m_CurrentClip->DurationLeft = m_CurrentClip->Duration;
    }
}
