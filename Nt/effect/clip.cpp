#include <iostream>
#include <fstream>
#include "./../wavWrite.h"
using namespace std;

// openFile clip saveFile
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

  // 

  // Clip

  //

  int clip = atoi(arguments[2]);

  datumIndex = 0;
  while (datumIndex < audioDataLength){
    short thisSample = audioData[datumIndex];
    if (thisSample > 0){
      if (thisSample > clip){
        thisSample = clip;
      }
    }
    else{
      if ((-1 * clip) > thisSample){
        thisSample = -1 * clip;
      }
    }
    audioData[datumIndex] = thisSample;;
    datumIndex++;
  }

  const char * saveFile = arguments[3];

  writeWAVData(saveFile, audioData, audioDataLength * 2, 44100, 1);
  return 0;    
}