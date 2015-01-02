#include <iostream>
#include <fstream>
using namespace std;

int main () {
  ifstream awav;
  awav.open("testWav.wav", std::ifstream::in);

  awav.seekg(0, awav.end);
  int length = awav.tellg();
  awav.seekg(0, awav.beg);

  int data [length];

  int datumIndex = 0;
  while (datumIndex < length){
    data[datumIndex] = awav.get();
    datumIndex++;
  }

  int numberOfChannels = data[22];

  datumIndex = 44;
  int audioDataLength = (length - 44) / 2;
  int audioData [audioDataLength];
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

  datumIndex = 0;
  while (datumIndex < audioDataLength){
    std::cout << datumIndex << " " << audioData[datumIndex] << "\n";
    datumIndex++;
  }

  //int audioData [length - 36]

  /*datumIndex = 0;
  while (datumIndex < length){
    //std::cout << datumIndex << "  " << data[datumIndex] << "\n";
    datumIndex++;
  }*/

  /*
  std::cout << "\n";
  std::cout << "THIS IS DATA " << std::hex << data;
  std::cout << "\n";
  */
  awav.close();

  /*
  ifstream awav ("testWav.wav");

  if (awav){
    std::cout << "THIS IS END : " << awav.end << "\n";
    awav.seekg(0, awav.end);
    int length = awav.tellg();
    std::cout << "THIS IS BEGINNING : " << awav.beg << "\n";
    awav.seekg(0, awav.beg);

    char * buffer = new char [length];

    std::cout << "Reading " << length << " LONG WAVE FILE \n";
    awav.read(buffer, length);

    if (awav){
      std::cout << "CHARS READ EPQF \n";
      std::cout << "THESERDATUM : \n";
      std::cout << buffer;
      std::cout << "\n";
    }
    else{
      std::cout << " CHARS READ NOPE \n";
    }
    awav.close();
    delete[] buffer;

  }
  */

  /*
  ifstream awav;
  awav.open("testWav.wav");

  char data[100];
  awav >> data;
  cout << data << "\n";
  cout << "POSITION?" << awav.seekg(4);
  awav >> data;
  cout << data << "\n";
  awav.seekg(4);
  awav >> data;
  cout << data << "\n";

  awav.close();
  */

  return 0;    
}