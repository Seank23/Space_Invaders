// Based on olcNoiseMaker implementation by OneLoneCoder (Javidx9)
#pragma once

#pragma comment(lib, "winmm.lib")

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <functional>

#include <Windows.h>

#include "AudioState.h"

namespace AudioEngine
{
	struct StreamParameters
	{
		std::wstring outputDevice;
		unsigned int sampleRate = 44100;
		unsigned int channels = 1;
		unsigned int blocks = 8;
		unsigned int blockSamples = 512;
	};

	template<class T>
	class AudioStream
	{
	public:
		AudioStream<T>();
		~AudioStream<T>();

		bool Create(StreamParameters& params);
		void Stop();

		double GetTime() { return m_GlobalTime; }
		void SetUserFunction(std::function<double(double)> func) { m_UserFunction = func; }

		bool Destroy()
		{
			Stop();
			return false;
		}

		double Clip(double sample, double max)
		{
			if (sample >= 0.0)
				return std::fmin(sample, max);
			else
				return std::fmax(sample, -max);
		}


	private:
		std::function<double(double)> m_UserFunction;

		unsigned int m_SampleRate;
		unsigned int m_Channels;
		unsigned int m_BlockCount;
		unsigned int m_BlockSamples;
		unsigned int m_CurrentBlock;

		T* m_BlockMemory;
		WAVEHDR* m_WaveHeaders;
		HWAVEOUT m_HardwareDevice;

		std::thread m_Thread;
		std::atomic<bool> m_Ready;
		std::atomic<unsigned int> m_BlocksFree;
		std::condition_variable m_BlockNotZero;
		std::mutex m_MuxBlockNotZero;

		std::atomic<double> m_GlobalTime;

		void MainThread();

		void waveOutProc(HWAVEOUT hWaveOut, UINT uMsg, DWORD dwParam1, DWORD dwParam2)
		{
			if (uMsg != WOM_DONE) return;

			m_BlocksFree++;
			std::unique_lock<std::mutex> lm(m_MuxBlockNotZero);
			m_BlockNotZero.notify_one();
		}

		static void CALLBACK waveOutProcWrap(HWAVEOUT hWaveOut, UINT uMsg, DWORD_PTR dwInstance, DWORD dwParam1, DWORD dwParam2)
		{
			((AudioStream*)dwInstance)->waveOutProc(hWaveOut, uMsg, dwParam1, dwParam2);
		}
	};
}