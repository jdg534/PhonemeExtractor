#include <iostream>
#include <string>

#include <Signal.h>

// https://doc.qt.io/qt-5/audiooverview.html
#include <QAudioFormat>
#include <QAudioDecoder>


int main(int argc, char *argv[])
{
	if (argc != 3) // argv[0] = executable name
	{
		std::cout << "Calling syntax: SoundFileToDftMag <path to sound file> <output .txt file>"  << std::endl;
		return 1;
	}

	
	const std::string inputFilePath = argv[1];
	const std::string outputFilePath = argv[2];

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
	decoder->read();

	
	
	delete decoder;

    return 0;
}
