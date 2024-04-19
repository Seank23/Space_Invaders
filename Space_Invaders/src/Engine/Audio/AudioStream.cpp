#include "AudioStream.h"
#include "AudioUtils.h"

namespace AudioEngine
{
	template<class T>
	AudioStream<T>::AudioStream(StreamParameters& params)
	{
		Create(params);
	}

	template<class T>
	AudioStream<T>::~AudioStream()
	{
		Destroy();
	}

	template<class T>
	bool AudioStream<T>::Create(StreamParameters& params)
	{
		m_Ready = false;
		m_SampleRate = params.sampleRate;
		m_Channels = params.channels;
		m_BlockCount = params.blocks;
		m_BlockSamples = params.blockSamples;
		m_BlocksFree = m_BlockCount;
		m_CurrentBlock = 0;
		m_BlockMemory = nullptr;
		m_WaveHeaders = nullptr;
		m_UserFunction = nullptr;

		std::vector<std::wstring> devices = AudioUtils::EnumerateDevices();
		auto currentDevice = std::find(devices.begin(), devices.end(), params.outputDevice);
		if (currentDevice != devices.end())
		{
			int deviceId = std::distance(devices.begin(), currentDevice);
			WAVEFORMATEX waveFormat;
			waveFormat.wFormatTag = WAVE_FORMAT_PCM;
			waveFormat.nSamplesPerSec = m_SampleRate;
			waveFormat.wBitsPerSample = sizeof(T) * 8;
			waveFormat.nChannels = m_Channels;
			waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
			waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
			waveFormat.cbSize = 0;

			if (waveOutOpen(&m_HardwareDevice, deviceId, &waveFormat, (DWORD_PTR)waveOutProcWrap, (DWORD_PTR)this, CALLBACK_FUNCTION) != S_OK)
				return Destroy();
		}

		m_BlockMemory = new T[m_BlockCount * m_BlockSamples];
		if (m_BlockMemory == nullptr)
			return Destroy();
		ZeroMemory(m_BlockMemory, sizeof(T) * m_BlockCount * m_BlockSamples);

		m_WaveHeaders = new WAVEHDR[m_BlockCount];
		if (m_WaveHeaders == nullptr)
			return Destroy();
		ZeroMemory(m_WaveHeaders, sizeof(WAVEHDR) * m_BlockCount);

		for (unsigned int n = 0; n < m_BlockCount; n++)
		{
			m_WaveHeaders[n].dwBufferLength = m_BlockSamples * sizeof(T);
			m_WaveHeaders[n].lpData = (LPSTR)(m_BlockMemory + (n * m_BlockSamples));
		}
		m_Ready = true;
		m_Thread = std::thread(&AudioStream::MainThread, this);

		std::unique_lock<std::mutex> lm(m_MuxBlockNotZero);
		m_BlockNotZero.notify_one();

		return true;
	}

	template<class T>
	void AudioStream<T>::Stop()
	{
		m_Ready = false;
		m_Thread.join();
	}

	template<class T>
	void AudioStream<T>::MainThread()
	{
		m_GlobalTime = 0.0;
		double ts = 1.0 / (double)m_SampleRate;

		T maxSampleT = (T)std::pow(2, (sizeof(T) * 8) - 1) - 1;
		double maxSample = (double)maxSampleT;
		T prevSample = 0;

		while (m_Ready)
		{
			if (m_BlocksFree == 0)
			{
				std::unique_lock<std::mutex> lm(m_MuxBlockNotZero);
				m_BlockNotZero.wait(lm);
			}

			m_BlocksFree--;

			if (m_WaveHeaders[m_CurrentBlock].dwFlags & WHDR_PREPARED)
				waveOutUnprepareHeader(m_HardwareDevice, &m_WaveHeaders[m_CurrentBlock], sizeof(WAVEHDR));

			T newSample = 0;
			int currentSample = m_CurrentBlock * m_BlockSamples;

			for (unsigned int n = 0; n < m_BlockSamples; n++)
			{
				if (m_UserFunction != nullptr)
					newSample = (T)(Clip(m_UserFunction(m_GlobalTime), 1.0) * maxSample);

				m_BlockMemory[currentSample + n] = newSample;
				prevSample = newSample;
				m_GlobalTime += ts;
			}

			waveOutPrepareHeader(m_HardwareDevice, &m_WaveHeaders[m_CurrentBlock], sizeof(WAVEHDR));
			waveOutWrite(m_HardwareDevice, &m_WaveHeaders[m_CurrentBlock], sizeof(WAVEHDR));
			m_CurrentBlock++;
			m_CurrentBlock %= m_BlockCount;
		}
	}
	template class AudioStream<short>;
}

