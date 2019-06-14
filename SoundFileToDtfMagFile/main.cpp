#include <string>
#include <iostream>
#include <fstream>

#include <chrono>
#include <thread>

#include <Signal.h>

// https://doc.qt.io/qt-5/audiooverview.html
#include <QAudioFormat>
#include <QAudioDecoder>
#include <QSound>

int main(int argc, char *argv[]);
void DumpWaveformToFileI16(const int16_t* waveFormToDump, const size_t nSamplesInWaveform, const char* outputFilePath);
void OnSoundBufferReady();

bool s_soundBufferReady;

class SoundDecoder : public QObject
{
public:
	SoundDecoder(const std::string& pathToSoundFile)
		: QObject(nullptr)
		, m_pathToSoundFile(pathToSoundFile)
		, m_finishedLoading(false)
		, m_soundData(nullptr)
		, m_sampleCount(0)
	{
	}

	virtual ~SoundDecoder()
	{
		if (m_soundData)
			delete[] m_soundData;
	}

	bool DecodeSound()
	{
		// need to get Qt to read in the file and get access to the QAudioBuffer
		QAudioFormat desiredFormat;
		desiredFormat.setChannelCount(1);
		desiredFormat.setCodec("audio/pcm"); // based off example code
		desiredFormat.setSampleType(QAudioFormat::SignedInt);
		desiredFormat.setSampleRate(44100);
		desiredFormat.setSampleSize(16);

		QAudioDecoder *decoder = new QAudioDecoder(nullptr);
		decoder->setAudioFormat(desiredFormat);
		decoder->setSourceFilename(m_pathToSoundFile.c_str());
		
		using namespace std;
		cout << "making connection to &QAudioDecoder::bufferReady" << endl;
		connect(decoder, &QAudioDecoder::bufferReady, this, &SoundDecoder::OnSoundBufferReady);
		// check the signals in https://doc.qt.io/qt-5/qaudiodecoder.html
		cout << "starting decode" << endl;
		decoder->start();

		while (!m_finishedLoading)
		{
			const chrono::seconds sleepDurection(2);
			this_thread::sleep_for(sleepDurection);
			cout << "Sleeping for " << sleepDurection.count() << " seconds" << endl;
		}
		
		cout << "disconnecting from &QAudioDecoder::bufferReady" << endl;
		disconnect(decoder, &QAudioDecoder::bufferReady, this, &SoundDecoder::OnSoundBufferReady);
		decoder->stop();
		QAudioBuffer sndBuffer = decoder->read();

		m_sampleCount = static_cast<uint>(sndBuffer.sampleCount());
		if (m_sampleCount == 0)
			return false;

		m_soundData = new int16_t[m_sampleCount];
		const size_t nBytesToMemCpy = sizeof(int16_t) * static_cast<size_t>(m_sampleCount);
		memcpy(m_soundData, sndBuffer.data(), nBytesToMemCpy);

		delete decoder;

	}

	
	void GetSoundData(int16_t** outStartOfSoundData, uint& sampleCount)
	{
		*outStartOfSoundData = m_soundData; // breaks encapsulation, refactor once a working version is commited
		sampleCount = m_sampleCount;
	}

private:
	void OnSoundBufferReady()
	{
		std::cout << __FUNCTION__  << " called decode finished"<< std::endl;
		m_finishedLoading = true;
	}

	const std::string m_pathToSoundFile;
	bool m_finishedLoading;
	int16_t* m_soundData;
	uint m_sampleCount;

};


int main(int argc, char *argv[])
{
	if (argc < 3) // argv[0] = executable name
	{
		std::cout << "Calling syntax: SoundFileToDftMag <path to sound file> <output .txt file> <Optional cut off frequency as double>"  << std::endl;
		return 1;
	}
	
	const std::string inputFilePath = argv[1];
	const std::string outputFilePath = argv[2];

	s_soundBufferReady = false;

	std::cout << "Attempting to load " << inputFilePath << std::endl;

	// QSound* sndFile = new QSound(inputFilePath.c_str());
	// delete sndFile;

	SoundDecoder sndDeCoder(inputFilePath);

	if (!sndDeCoder.DecodeSound())
	{
		std::cout << "failed to load " << inputFilePath << std::endl;
		return 2;
	}

	std::cout << inputFilePath << " loaded" << std::endl;

	uint numberOfSoundSamples = 0;
	int16_t* soundData = nullptr;
	sndDeCoder.GetSoundData(&soundData, numberOfSoundSamples);
	
	std::cout << inputFilePath << " has " << numberOfSoundSamples << " samples" << std::endl;

	double filterCutoffFrequency = 0.25; // value = 0.0 < X < 1.0
	if (argc >= 4)
	{
		try
		{
			filterCutoffFrequency = strtod(argv[3], NULL);
		}
		catch (...)
		{
			filterCutoffFrequency = 0.25;
		}
	}
	
	// low pass filter, 27 samples should do
	size_t filterSigElementCount = 27;
	if (argc >= 5)
	{
		try
		{
			filterSigElementCount = static_cast<size_t>(atoi(argv[4]));
		}
		catch (...)
		{
			filterSigElementCount = 27;
		}
	}

	int16_t* lowPassFilter = new int16_t[filterSigElementCount];
	Signal::Filters::Windowed::SyncLowPassI16(lowPassFilter, filterSigElementCount, filterCutoffFrequency);

	std::cout << "Generated low pass filter with " << filterSigElementCount << " samples and a normalised cut off frequency of " << filterCutoffFrequency << std::endl;

	const size_t filteredWaveformSampleCount = static_cast<size_t>(numberOfSoundSamples) + filterSigElementCount;
	int16_t* filteredSignal = new int16_t[filteredWaveformSampleCount];

	Signal::Convolution::ConvolutionI16(soundData, static_cast<size_t>(numberOfSoundSamples), lowPassFilter, filterSigElementCount, filteredSignal);
	std::cout << "Calculated filtered signal" << std::endl;
	
	const size_t dftArraySize = (filteredWaveformSampleCount / 2) + 1;
	int16_t* dftRealComponent = new int16_t[dftArraySize];
	int16_t* dftComplexComponent = new int16_t[dftArraySize];
	int16_t* dftMag = new int16_t[dftArraySize];
	std::cout << "Calculating Discrete Fourier Transform" << std::endl;
	Signal::FourierTransforms::DiscreteFourierTransformI16(filteredSignal, filteredWaveformSampleCount, dftRealComponent, dftComplexComponent);
	std::cout << "Calculating Discrete Fourier Transform Magnitude" << std::endl;
	Signal::FourierTransforms::DiscreteFourierTransformMagnitudei16(dftMag, dftRealComponent, dftComplexComponent, dftArraySize);

	std::cout << "Writing Discrete Fourier Transform Magnitude to " << outputFilePath << std::endl;
	DumpWaveformToFileI16(dftMag, dftArraySize, outputFilePath.c_str());
	std::cout << "DONE" << std::endl;

	delete[] dftRealComponent;
	delete[] dftComplexComponent;
	delete[] dftMag;
	delete[] filteredSignal;
	delete[] lowPassFilter;

    return 0;
}

void DumpWaveformToFileI16(const int16_t* waveFormToDump, const size_t nSamplesInWaveform, const char* outputFilePath)
{
	std::ofstream output(outputFilePath);
	for (size_t i = 0; i < nSamplesInWaveform; ++i)
	{
		output << waveFormToDump[i] << std::endl;
	}
	output.flush();
	output.close();
}

void OnSoundBufferReady()
{
	s_soundBufferReady = true;
}