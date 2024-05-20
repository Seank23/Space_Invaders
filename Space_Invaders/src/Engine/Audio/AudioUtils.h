#pragma once

#include <vector>
#include <string>

#include <Windows.h>

namespace AudioEngine
{
	class AudioUtils
	{
	public:
		static std::vector<std::wstring> EnumerateDevices()
		{
			int deviceCount = waveOutGetNumDevs();
			std::vector<std::wstring> devices;
			WAVEOUTCAPS waveOutCaps;
			for (int n = 0; n < deviceCount; n++)
			{
				if (waveOutGetDevCaps(n, &waveOutCaps, sizeof(WAVEOUTCAPS)) == S_OK)
					devices.push_back(waveOutCaps.szPname);
			}
			return devices;
		}

		static double ToSquareWave(double sample)
		{
			return sample > 0.0 ? 1.0 : -1.0;
		}

		static constexpr double PI = 3.1415926;

		static uint32_t PCG_Hash(uint32_t input)
		{
			uint32_t state = input * 747796405u + 2891336453u;
			uint32_t word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
			return (word >> 22u) ^ word;
		}

		static float GetNoiseSample(uint32_t& seed)
		{
			seed = PCG_Hash(seed);
			return ((float)seed / (float)UINT32_MAX) * 2.0f - 1.0f;
		}
	};
}