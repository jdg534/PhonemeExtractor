#include <string>
#include <iostream>
#include <fstream>


#include <Signal.h>

// https://doc.qt.io/qt-5/audiooverview.html
#include <QAudioFormat>
#include <QAudioDecoder>

int main(int argc, char *argv[]);
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

	// need to get Qt to read in the file and get access to the QAudioBuffer
	QAudioFormat desiredFormat;
	desiredFormat.setChannelCount(1);
	desiredFormat.setCodec("audio/pcm"); // based off example code
	desiredFormat.setSampleType(QAudioFormat::SignedInt);
	desiredFormat.setSampleRate(44100);
	desiredFormat.setSampleSize(16);

	QAudioDecoder *decoder = new QAudioDecoder(nullptr);
	decoder->setAudioFormat(desiredFormat);
	decoder->setSourceFilename(argv[1]);
	QAudioBuffer sndBuffer = decoder->read();

	const size_t inputSndBufferSampleCount = static_cast<size_t>(sndBuffer.sampleCount());
	if (inputSndBufferSampleCount == 0)
	{
		std::cout << "failed to load " << inputFilePath << std::endl;
		return 2;
	}

	std::cout << inputFilePath << " loaded" << std::endl;

	
	const QAudioFormat::SampleType sampleType = sndBuffer.format().sampleType();
	const int sndBufferByteCount = sndBuffer.byteCount();
	int16_t* bufferCorrectType = (int16_t*) sndBuffer.data();
	int16_t* bufferCopy = new int16_t[inputSndBufferSampleCount];
	memcpy(bufferCopy, bufferCorrectType, static_cast<size_t>(sndBufferByteCount));
	
	std::cout << inputFilePath << " has " << inputSndBufferSampleCount << " samples" << std::endl;

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

	const size_t filteredWaveformSampleCount = inputSndBufferSampleCount + filterSigElementCount;
	int16_t* filteredSignal = new int16_t[filteredWaveformSampleCount];

	Signal::Convolution::ConvolutionI16(bufferCopy, inputSndBufferSampleCount, lowPassFilter, filterSigElementCount, filteredSignal);
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

	delete[]  dftRealComponent;
	delete[] dftComplexComponent;
	delete[] dftMag;
	delete[] filteredSignal;
	delete[] lowPassFilter;
	delete[] bufferCopy;
	delete decoder;

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