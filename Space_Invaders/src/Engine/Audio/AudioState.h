#pragma once

#include <vector>
#include <string>

namespace AudioEngine
{
	struct AudioClip
	{
		AudioClip()
			: Name(""), Duration(0), DurationLeft(0.0), IsSquareWave(false)
		{}
		AudioClip(std::string name, std::vector<double> frequencies, std::vector<int> timings, std::vector<int> sequence, int duration, bool isSquareWave)
			: Name(name), Frequencies(frequencies), Timings(timings), Sequence(sequence), Duration(duration), DurationLeft((double)duration), IsSquareWave(isSquareWave)
		{}

		std::string Name;
		std::vector<double> Frequencies;
		std::vector<int> Timings;
		std::vector<int> Sequence;
		int Duration;
		double DurationLeft;
		bool IsSquareWave;
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

