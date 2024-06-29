#pragma once

#include <vector>
#include <string>
#include <functional>

namespace AudioEngine
{
	struct AudioClip
	{
		AudioClip()
			: Name(""), Duration(0), DurationLeft(0.0), IsSquareWave(false), StartTime(0.0), Volume(0.0)
		{}
		AudioClip(std::string name, std::function<double(double)> audioFunction, int duration, bool isSquareWave, double volume)
			: Name(name), AudioFunction(audioFunction), Duration(duration), DurationLeft((double)duration), IsSquareWave(isSquareWave), StartTime(0.0), Volume(volume)
		{}

		std::string Name;
		std::function<double(double)> AudioFunction;
		int Duration;
		double DurationLeft;
		bool IsSquareWave;
		double StartTime;
		double Volume;
	};

	class AudioState
	{
	public:
		AudioState();
		~AudioState();

		void AddClip(AudioClip clip) { m_Clips.push_back(clip); }
		AudioClip* GetClip(std::string name);

	private:
		std::vector<AudioClip> m_Clips;
	};
}

