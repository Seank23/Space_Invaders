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
	};
}