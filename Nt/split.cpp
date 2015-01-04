#include <iostream>
#include <fstream>
#include "./wavWrite.h"
using namespace std;

// openFile splitAt saveFile0 saveFile1
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

  // Splitting

  //

  int splitAt = atoi(arguments[2]);

  short firstFile [splitAt];
  short secondFile [audioDataLength - splitAt];

  datumIndex = 0;
  while (datumIndex < splitAt){
    firstFile[datumIndex] = audioData[datumIndex];
    datumIndex++;
  }
  while (datumIndex < audioDataLength){
    secondFile[datumIndex - splitAt] = audioData[datumIndex];
    datumIndex++;
  }

  const char * saveFile0 = arguments[3];
  const char * saveFile1 = arguments[4];

  writeWAVData(saveFile0, firstFile , splitAt * 2, 44100, 1);
  writeWAVData(saveFile1, secondFile, (audioDataLength - splitAt) * 2, 44100, 1);

  return 0;    
}