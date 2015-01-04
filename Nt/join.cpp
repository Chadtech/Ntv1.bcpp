#include <iostream>
#include <fstream>
#include "./wavWrite.h"
using namespace std;

// fileName0 fileName1 saveFileName
int main (int argumentCount, char * arguments[]) {
  const char * fileName0 = arguments[1];
  const char * fileName1 = arguments[2];

  //

  // FILE 0

  //

  ifstream wav0;
  wav0.open(fileName0, std::ifstream::in);

  wav0.seekg(0, wav0.end);
  int length = wav0.tellg();
  wav0.seekg(0, wav0.beg);

  int data0 [length];

  int datumIndex = 0;
  while (datumIndex < length){
    data0[datumIndex] = wav0.get();
    datumIndex++;
  }

  datumIndex = 44;
  int audioDataLength0 = (length - 44) / 2;
  short audioData0 [audioDataLength0];
  int audioDatumIndex = 0;
  int thisSampleDatum [2];

  while (datumIndex < length){
    if ((datumIndex % 2) == 0){
      thisSampleDatum[0] = data0[datumIndex];
    }
    else{
      thisSampleDatum[1] = data0[datumIndex];
      short sample = thisSampleDatum[1] * 256;
      sample += thisSampleDatum[0];
      audioData0[audioDatumIndex] = sample;
      audioDatumIndex++;
    }
    datumIndex++;
  }

  wav0.close();

  //

  // FILE 1

  //

  ifstream wav1;
  wav1.open(fileName1, std::ifstream::in);

  wav1.seekg(0, wav1.end);
  length = wav1.tellg();
  wav1.seekg(0, wav1.beg);

  int data1 [length];

  datumIndex = 0;
  while (datumIndex < length){
    data1[datumIndex] = wav1.get();
    datumIndex++;
  }

  datumIndex = 44;
  int audioDataLength1 = (length - 44) / 2;
  short audioData1 [audioDataLength1];
  audioDatumIndex = 0;

  while (datumIndex < length){
    if ((datumIndex % 2) == 0){
      thisSampleDatum[0] = data1[datumIndex];
    }
    else{
      thisSampleDatum[1] = data1[datumIndex];
      short sample = thisSampleDatum[1] * 256;
      sample += thisSampleDatum[0];
      audioData1[audioDatumIndex] = sample;
      audioDatumIndex++;
    }
    datumIndex++;
  }

  wav1.close();

  // 

  // JOINING

  //

  short joinedAudioData [audioDataLength0 + audioDataLength1];

  datumIndex = 0;
  while (datumIndex < audioDataLength0){
    joinedAudioData[datumIndex] = audioData0[datumIndex];
    datumIndex++;
  }
  datumIndex = 0;
  while (datumIndex < audioDataLength1){
    joinedAudioData[datumIndex + audioDataLength0] = audioData1[datumIndex];
    datumIndex++;
  }

  const char * saveName = arguments[3];

  writeWAVData(saveName, joinedAudioData , (audioDataLength0 + audioDataLength1) * 2, 44100, 1);

  return 0;    
}