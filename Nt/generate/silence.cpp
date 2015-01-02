#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "./../wavWrite.h"

// Arguments are:
// fileName sustain

int main (int argumentCount, char * arguments[]){
  double pi = 3.14159;
  int maxAmplitude = 32767;

  const char * fileName = arguments[1];

  int sustain;
  std::string sustainAsString = arguments[2];

  int stringIndex = 0;
  while (stringIndex < sustainAsString.size()){
    int thisDigitOfSustain = sustainAsString[stringIndex] - 48;
    sustain *= 10;
    sustain += thisDigitOfSustain;
    stringIndex++;
  }

  short output[sustain];
  short silence = 0;
  int outputIndex = 0;
  while (outputIndex < sustain){
    output[outputIndex] = silence;
    outputIndex++;
  }

  writeWAVData(fileName, output, sustain, 44100, 1);

  return 0;
}