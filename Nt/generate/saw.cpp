#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "./../wavWrite.h"

// Arguments are:
// fileName frequency duration harmonicCount enharmonicity

int main (int argumentCount, char * arguments[]){
  const double pi = 3.14159;
  const int maxAmplitude = 32767;

  const char * fileName = arguments[1];

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

  int harmonicCount = atof(arguments[4]);

  double enharmonicity = atof(arguments[5]);

  short output[sustain];
  
  int outputIndex = 0;
  while (outputIndex < sustain){
    output[outputIndex] = 0;
    outputIndex++;
  }

  int volumeNumerator = 2 * harmonicCount;
  int volumeDenominator = harmonicCount - 1;
  volumeDenominator = pow(volumeDenominator, 2);
  volumeDenominator++;
  volumeDenominator = pow(volumeDenominator, 0.5);
  volumeDenominator *= pi;

  float volumeAdjust = volumeNumerator;
  volumeAdjust /= volumeDenominator;
  volumeAdjust = 1 - volumeAdjust;

  int harmonic = 1;
  while (harmonic < harmonicCount){
    outputIndex = 0;
    while (outputIndex < sustain){

      float enharmonic = 1;
      if (enharmonicity != 0){
        enharmonic = 1 + enharmonicity;
        enharmonic = pow(enharmonic, harmonic - 1);
      }

      float thisSample = maxAmplitude;
      if ((harmonic % 2) == 1){
        thisSample *= -1;
      }
      thisSample /= harmonic;

      float sineArgument = outputIndex * pi * 2;
      sineArgument *= harmonic * enharmonic;
      sineArgument *= frequency;

      thisSample *= sin(sineArgument);

      short sample = thisSample;
      sample *= volumeAdjust;

      output[outputIndex] += sample;
      outputIndex++;

    }
    harmonic++;
  }

  writeWAVData(fileName, output, sustain * 2, 44100, 1);

  return 0;
}