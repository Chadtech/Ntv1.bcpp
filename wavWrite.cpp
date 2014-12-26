#include <iostream>
#include <fstream>

template <typename T>
void write(std::ofstream& stream, const T& t) {
  stream.write((const char*)&t, sizeof(T));
}

template <typename T>
void writeFormat(std::ofstream& stream) {
  write<short>(stream, 1);
}

template <>
void writeFormat<float>(std::ofstream& stream) {
  write<short>(stream, 3);
}

template <typename SampleType>
void writeWAVData(
  char const* outFile,
  SampleType* buf,
  size_t bufSize,
  int sampleRate,
  short channels)
{
  std::ofstream stream(outFile, std::ios::binary);
  stream.write("RIFF", 4);
  write<int>(stream, 36 + bufSize);
  stream.write("WAVE", 4);
  stream.write("fmt ", 4);
  write<int>(stream, 16);
  writeFormat<SampleType>(stream);                                // Format
  write<short>(stream, channels);                                 // Channels
  write<int>(stream, sampleRate);                                 // Sample Rate
  write<int>(stream, sampleRate * channels * sizeof(SampleType)); // Byterate
  write<short>(stream, channels * sizeof(SampleType));            // Frame size
  write<short>(stream, 8 * sizeof(SampleType));                   // Bits per sample
  stream.write("data", 4);
  stream.write((const char*)&bufSize, 4);
  stream.write((const char*)buf, bufSize);
}

int main() {
  int datasLength = 2646000 * 2;
  short ourData [datasLength];
  int maxAmplitude = 65536;
  int datumIndex = 0;

  short bigValue = 16000;
  short smallValue = -16000;

  while (datumIndex < datasLength){
    int phasePoint = datumIndex % 80;
    phasePoint -= 40;
    float thisAmplitude = phasePoint;
    thisAmplitude = thisAmplitude / 80;
    short thisSample = thisAmplitude * maxAmplitude;

    ourData[datumIndex] = thisSample;

    ++datumIndex;
  };

  writeWAVData("cppTest.wav", ourData, datasLength, 44100, 1);

  return 0;
};

