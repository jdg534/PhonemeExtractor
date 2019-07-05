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
void LoadWavFile(double** OUT_samples, size_t& OUT_nSamples, const std::string& fileStr); // assume uses heap if OUT_samples is changed
void DumpWaveformToFileI16(const int16_t* waveFormToDump, const size_t nSamplesInWaveform, const char* outputFilePath);
void DumpWaveformToFileD(const double* waveFormToDump, const size_t nSamplesInWaveform, const char* outputFilePath);

int main(int argc, char *argv[])
{
	if (argc < 3) // argv[0] = executable name
	{
		std::cout << "Calling syntax: SoundFileToDftMag <path to sound file> <INT filter window size>"  << std::endl;
		return 1;
	}
	
	const std::string inputFilePath = argv[1];

	int windowFilterSize = std::atoi(argv[2]);
	
	/* new plan, mimic Audacity's approach for frequency analysis
	use blackman window filter
	the drop down is labeled "Spectrum" their docs say it's an FFT	
	*/

	std::cout << "Attempting to load " << inputFilePath << std::endl;

	size_t numberOfSoundSamples = 0;
	double* soundData = nullptr;

	LoadWavFile(&soundData, numberOfSoundSamples, inputFilePath);

	if (soundData == nullptr)
	{
		std::cout << "failed to load " << inputFilePath <<  std::endl;
		return 2;
	}

	std::cout << inputFilePath << " loaded" << std::endl;
	std::cout << inputFilePath << " has " << numberOfSoundSamples << " samples" << std::endl;

	// corrected plan: blackman window filter, convolution with the window,  DFT

	const size_t backmanWindowSampleCount = static_cast<size_t>(windowFilterSize);
	double* backmanFilter = new double[backmanWindowSampleCount];
	std::cout << "generating " << backmanWindowSampleCount << " sample blackman window filter" << std::endl;
	Signal::Filters::Windowed::BlackmanD(backmanFilter, backmanWindowSampleCount);

	const size_t postFilterWaveformSampleCount = numberOfSoundSamples + backmanWindowSampleCount;
	double* filteredWaveform = new double[postFilterWaveformSampleCount];
	std::cout << "calculating post filter waveform" << std::endl;
	Signal::Convolution::ConvolutionD(soundData, numberOfSoundSamples, backmanFilter, backmanWindowSampleCount, filteredWaveform);

	const size_t dftComponentArraySize = (postFilterWaveformSampleCount / 2) + 1;
	double* dftRealComponent = new double[dftComponentArraySize];
	double* dftComplexComponent = new double[dftComponentArraySize];
	double* dftMag = new double[dftComponentArraySize];
	std::cout << "Calculating DFT on filtered waveform" << std::endl;
	Signal::FourierTransforms::DiscreteFourierTransformD(filteredWaveform, postFilterWaveformSampleCount, dftRealComponent, dftComplexComponent);
	std::cout << "Calculating DFT magnitude on filtered waveform" << std::endl;
	Signal::FourierTransforms::DiscreteFourierTransformMagnitudeD(dftMag, dftRealComponent, dftComplexComponent, dftComponentArraySize);

	// write output files
	const size_t inputFilePathExtSubStr = inputFilePath.find_last_of(".");
	const std::string outFileStart = inputFilePath.substr(0, inputFilePathExtSubStr);

	DumpWaveformToFileD(soundData, numberOfSoundSamples, (outFileStart + "_waveformDump.txt").c_str());
	DumpWaveformToFileD(backmanFilter, backmanWindowSampleCount, (outFileStart + "_filter.txt").c_str());
	DumpWaveformToFileD(filteredWaveform, postFilterWaveformSampleCount, (outFileStart + "_filted_waveform.txt").c_str());
	DumpWaveformToFileD(dftRealComponent, dftComponentArraySize, (outFileStart + "_dft_real.txt").c_str());
	DumpWaveformToFileD(dftComplexComponent, dftComponentArraySize, (outFileStart + "_dft_complex.txt").c_str());
	DumpWaveformToFileD(dftMag, dftComponentArraySize, (outFileStart + "_dft_mag.txt").c_str());

	// clean up
	delete[] soundData;
	delete[] backmanFilter;
	delete[] filteredWaveform;
	delete[] dftRealComponent;
	delete[] dftComplexComponent;
	delete[] dftMag;

    return 0;
}

void LoadWavFile(double** samples, size_t& nSamples, const std::string& fileStr)
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
	int16_t* readSamples = new int16_t[nSamples];
	std::memset(readSamples, 0, nSamples);
	// need to check that this is reading correctly
	inFile.read(reinterpret_cast<char*>(readSamples), dataChunkHeader.chunkSize);
	inFile.close();

	// copy readSamples to samples

	*samples = new double[nSamples];

	constexpr double scaleToDoubleRange = 1.0 / 65535.0;

	int16_t currentSample = 0;
	double convertion = 0.0;
	for (size_t i = 0; i < nSamples; ++i)
	{
		currentSample = readSamples[i];
		convertion = static_cast<double>(currentSample);
		convertion *= scaleToDoubleRange;
		samples[0][i] = convertion;
	}
	delete[] readSamples;
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

void DumpWaveformToFileD(const double* waveFormToDump, const size_t nSamplesInWaveform, const char* outputFilePath)
{
	std::ofstream output(outputFilePath);
	for (size_t i = 0; i < nSamplesInWaveform; ++i)
	{
		output << waveFormToDump[i] << std::endl;
	}
	output.flush();
	output.close();
}