#include <iostream>
#include <fstream>
#include "./../wavWrite.h"
using namespace std;

// openFile convolveSeed degree saveFile
int main (int argumentCount, char * arguments[]) {

  //

  // Open File

  //

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
      //std::cout << audioData[audioDatumIndex] << "\n";
      audioDatumIndex++;
    }
    datumIndex++;
  }

  wav.close();

  //

  // Open Convolve Seed

  //
  
  const char * convolveSeedFileName = arguments[2];

  ifstream convolveSeedFile;
  convolveSeedFile.open(convolveSeedFileName, std::ifstream::in);

  convolveSeedFile.seekg(0, convolveSeedFile.end);
  int convolveSeedFileLength = convolveSeedFile.tellg();
  convolveSeedFile.seekg(0, convolveSeedFile.beg);

  int convolveSeedFileData [length];

  datumIndex = 0;
  while (datumIndex < convolveSeedFileLength){
    convolveSeedFileData[datumIndex] = convolveSeedFile.get();
    datumIndex++;
  }

  datumIndex = 44;
  int convolveSeedLength = (convolveSeedFileLength - 44) / 2;
  short convolveSeed [convolveSeedLength];
  int convolveSeedDatumIndex = 0;

  while (datumIndex < convolveSeedFileLength){
    if ((datumIndex % 2) == 0){
      thisSampleDatum[0] = convolveSeedFileData[datumIndex];
    }
    else{
      thisSampleDatum[1] = convolveSeedFileData[datumIndex];
      short sample = thisSampleDatum[1] * 256;
      sample += thisSampleDatum[0];
      convolveSeed[audioDatumIndex] = sample;
      convolveSeedDatumIndex++;
    }
    datumIndex++;
  }

  convolveSeedFile.close();

  // 

  // Convolve

  //

  float factor = atof(arguments[3]);

  short convolvedData [convolveSeedLength + audioDataLength];
  int outputIndex = 0;
  while (outputIndex < (convolveSeedLength + audioDataLength)){
    convolvedData[outputIndex] = 0;
    outputIndex++;
  }

  audioDatumIndex = 0;
  int convolveSeedIndex = 0;
  while (audioDatumIndex < audioDataLength){
    convolveSeedIndex = 0;
    while (convolveSeedIndex < convolveSeedLength){
      short sample = audioData[audioDatumIndex];
      float fade = convolveSeed[convolveSeedIndex];
      fade /= 32767;
      sample *= fade;
      sample *= factor;
      convolvedData[audioDatumIndex + convolveSeedIndex] += sample;
      convolveSeedIndex++;
    }
    audioDatumIndex++;
  }

  const char * saveFile = arguments[4];

  writeWAVData(saveFile, convolvedData, (convolveSeedLength + audioDataLength) * 2, 44100, 1);
  return 0;    
}