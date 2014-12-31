#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "./../wavWrite.h"

// fileName frequency duration

int main (int argumentCount, char * arguments[]){
  double pi = 3.14159;
  int maxAmplitude = 32767;

  const char * fileName = arguments[1];

  std::string wavFileName = "";


  double frequency = atof(arguments[2]);
  frequency /= 44100;
  int sustain;
  std::string sustainAsString = arguments[3];


  int stringIndex = 0;
  while (stringIndex < sustainAsString.size()){
    int thisDigitOfSustain = sustainAsString[stringIndex] - 48;
    sustain *= 10;
    sustain += thisDigitOfSustain;
    stringIndex++;
  }

  short output[sustain];
  int outputIndex = 0;
  while (outputIndex < sustain){
    short thisSample = maxAmplitude * sin(pi * frequency * outputIndex * 2);
    output[outputIndex] = thisSample;
    outputIndex++;
  }

  writeWAVData(fileName, output, sustain, 44100, 1);

  return 0;
}