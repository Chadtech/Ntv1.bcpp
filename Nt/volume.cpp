#include <iostream>
#include <fstream>
#include "./wavWrite.h"
using namespace std;

// fileNameToOpen fileNameToSave newVolume
int main (int argumentCount, char * arguments[]) {
  const char * fileName = arguments[1];

  ifstream wav;
  wav.open(fileName, std::ifstream::in);

  wav.seekg(0, wav.end);
  int length = wav.tellg();
  wav.seekg(0, wav.beg);

  int data [length];

  int datumIndex = 0;
  while (datumIndex < length){
    data[datumIndex] = wav.get();
    datumIndex++;
  }

  datumIndex = 44;
  int audioDataLength = (length - 44) / 2;
  short audioData [audioDataLength];
  int audioDatumIndex = 0;
  int thisSampleDatum [2];

  while (datumIndex < length){
    if ((datumIndex % 2) == 0){
      thisSampleDatum[0] = data[datumIndex];
    }
    else{
      thisSampleDatum[1] = data[datumIndex];
      short sample = thisSampleDatum[1] * 256;
      sample += thisSampleDatum[0];
      audioData[audioDatumIndex] = sample;
      audioDatumIndex++;
    }
    datumIndex++;
  }

  wav.close();

  double newVolume = atof(arguments[3]);

  datumIndex = 0;
  while (datumIndex < audioDataLength){
    float thisSample = audioData[datumIndex];
    thisSample = thisSample * newVolume;
    audioData[datumIndex] = thisSample;
    datumIndex++;
  }

  const char * saveName = arguments[2];
  writeWAVData(saveName, audioData, audioDataLength * 2, 44100, 1);

  return 0;    
}