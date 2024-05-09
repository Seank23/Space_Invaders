#pragma once

#include "Engine/Audio/AudioStream.h"
#include "Engine/Audio/AudioState.h"

namespace SpaceInvaders
{
	class AudioHandler
	{
	public:
		AudioHandler(std::wstring device);
		~AudioHandler();

		void PlayClip(std::string clipName);
		void StopClip(std::string clipName);
		bool IsClipActive(std::string clipName);
		void OnUpdate(float ts);

	private:
		double WindowFunction(double duration, double durationLeft);

		AudioEngine::AudioStream<short>* m_Stream;
		AudioEngine::AudioState* m_State;
		AudioEngine::StreamParameters* m_StreamParams;
		std::vector<AudioEngine::AudioClip*> m_CurrentClips;
		std::vector<std::string> m_CurrentClipList;

		float m_Volume;
		double m_CurrentTime;
	};
}

