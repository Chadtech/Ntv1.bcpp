#include <iostream>
#include <fstream>
#include "./../wavWrite.h"
#include <cmath>
using namespace std;

// openFile shift saveFile
int main (int argumentCount, char * arguments[]) {
  const char * openFile = arguments[1];

  ifstream wav;
  wav.open(openFile, std::ifstream::in);

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

  double shift = atof(arguments[2]);

  // 

  // Shifting

  //

  if (shift != 0){
    short shiftedData [audioDataLength + 1];

    if (shift > 0){
      shiftedData[0] = 0;
      datumIndex = 0;
      while (datumIndex < audioDataLength){
        shiftedData[datumIndex + 1] = audioData[datumIndex];
        datumIndex++;
      }
    }
    else{
      shiftedData[audioDataLength] = 0;
      datumIndex = 0;
      while (datumIndex < audioDataLength){
        shiftedData[datumIndex] = audioData[datumIndex];
        datumIndex++;
      }
    }

    shift = std::abs (shift);

    short averagedData [audioDataLength + 1];
    datumIndex = 0;
    while (datumIndex < (audioDataLength)){
      float thisSample = shiftedData[datumIndex] * (1 - shift);
      thisSample += shiftedData[datumIndex + 1] * shift;
      averagedData[datumIndex] = thisSample;
      datumIndex++;
    }
    averagedData[audioDataLength] = shiftedData[audioDataLength] * (1 - shift);

    const char * saveFile = arguments[3];

    writeWAVData(saveFile, averagedData, (audioDataLength + 1) * 2, 44100, 1);
  }

  return 0;    
}