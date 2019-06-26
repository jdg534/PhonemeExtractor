#include <string>
#include <iostream>
#include <fstream>

#include <chrono>
#include <thread>

#include <cstdint>

#include <Signal.h> // 

// this is based off: http://www-mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/WAVE.html

// .wav file headers
struct RiffHeader
{
	char riffStr[4]; // "RIFF"
	std::int32_t chunkSize;
};

struct WaveHeader
{
	char waveStr[4]; // "WAVE"
	char fmtStr[4]; // "fmt "
	std::int32_t chunkSize; // 16 expected
};

struct WaveformDescHeader
{
	std::int16_t wFormatTag;
	std::int16_t nChannels;
	std::int32_t nSamplesPerSec;
	std::int32_t nAvgBytesPerSec;
	std::int16_t nBlockAlign;
	std::int16_t wBitsPerSample;
};

struct DataChunkHeader
{
	char idStr[4]; // "data"
	std::int32_t chunkSize; // n bytes to read?
};

int main(int argc, char *argv[]);
void LoadWavFile(int16_t** OUT_samples, size_t& OUT_nSamples, const std::string& fileStr); // assume uses heap if OUT_samples is changed
void DumpWaveformToFileI16(const int16_t* waveFormToDump, const size_t nSamplesInWaveform, const char* outputFilePath);

int main(int argc, char *argv[])
{
	if (argc < 3) // argv[0] = executable name
	{
		std::cout << "Calling syntax: SoundFileToDftMag <path to sound file> <output .txt file> <Optional cut off frequency as double>"  << std::endl;
		return 1;
	}
	
	const std::string inputFilePath = argv[1];
	const std::string outputFilePath = argv[2];

	

	std::cout << "Attempting to load " << inputFilePath << std::endl;

	size_t numberOfSoundSamples = 0;
	int16_t* soundData = nullptr;

	LoadWavFile(&soundData, numberOfSoundSamples, inputFilePath);

	if (soundData == nullptr)
	{
		std::cout << "failed to load " << inputFilePath <<  std::endl;
		return 2;
	}

	std::cout << inputFilePath << " loaded" << std::endl;

	
	
	
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

	delete[] soundData;
	delete[] dftRealComponent;
	delete[] dftComplexComponent;
	delete[] dftMag;
	delete[] filteredSignal;
	delete[] lowPassFilter;

    return 0;
}

void LoadWavFile(int16_t** samples, size_t& nSamples, const std::string& fileStr)
{
	std::ifstream inFile(fileStr, std::ios::binary);

	if (!inFile.good())
		return;

	// the file exists

	RiffHeader riffHeader;
	WaveHeader waveHeader;
	WaveformDescHeader waveformDescHeader;
	DataChunkHeader dataChunkHeader;

	inFile.read(reinterpret_cast<char*>(&riffHeader), sizeof(RiffHeader));
	inFile.read(reinterpret_cast<char*>(&waveHeader), sizeof(WaveHeader));
	inFile.read(reinterpret_cast<char*>(&waveformDescHeader), sizeof(WaveformDescHeader));
	inFile.read(reinterpret_cast<char*>(&dataChunkHeader), sizeof(DataChunkHeader));

	if (waveformDescHeader.wBitsPerSample != 16 || waveformDescHeader.nChannels != 1)
	{
		std::cout << "could read " << fileStr << " but the audio data needs to be 16 bit pcm with only 1 channel" << std::endl;
		std::cout << "bits per sample reported as " << waveformDescHeader.wBitsPerSample << " bit with " << waveformDescHeader.nChannels << " channels" << std::endl;
	}

	nSamples = static_cast<size_t>(dataChunkHeader.chunkSize / 2); // dataChunkHeader.chunkSize is in bytes, int16 takes 2 bytes per sample
	*samples = new int16_t[nSamples];
	std::memset(*samples, 0, nSamples);

	// need to check that this is reading correctly
	inFile.read(reinterpret_cast<char*>(*samples), dataChunkHeader.chunkSize);
	inFile.close();

#ifdef _DEBUG
	DumpWaveformToFileI16(*samples, nSamples, "ReadWaveFormDump.txt"); // needed to check the samples are being read correctly, use gnuplot 
#endif // _DEBUG
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
