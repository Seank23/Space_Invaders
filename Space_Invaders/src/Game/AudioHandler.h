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

	private:
		AudioEngine::AudioStream<short>* m_Stream;
		AudioEngine::AudioState* m_State;
		AudioEngine::StreamParameters* m_StreamParams;
		AudioEngine::AudioClip* m_CurrentClip;

		float m_Volume;
	};
}

