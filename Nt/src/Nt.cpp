#include <nan.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// For sine function
#include <math.h>

#include "./generate/sineGenerate.h"

#include "./wavWrite.h"

using namespace v8;
using v8::String;

NAN_METHOD(version){
  NanScope();
  const char * ntVersion0 = "ntv1bcpp";
  Local <String> ntVersion1 = NanNew<String>(ntVersion0);
  NanReturnValue(ntVersion1);
}

// Arguments are:
// filename frequency duration
NAN_METHOD(sineGenerate){
  NanScope();

  v8::String::Utf8Value param1(args[0]->ToString());
  std::string fileName0 = std::string(*param1);
  const char * fileName = fileName0.c_str();

  double frequency = args[1]->NumberValue();
  frequency /= 44100;

  int sustain = args[2]->Uint32Value();

  short * audio = new short[sustain];
  int confirmation = sineGenerate1(frequency, sustain, audio);

  writeWAVData( fileName, audio, sustain * 2, 44100, 1 );

  NanReturnUndefined();
}

  // Local<Array> output = NanNew<Array>(sustain);

  // int sampleIndex = 0;
  // while (sampleIndex < sustain){
  //   short sample = audio[sampleIndex];
  //   output->Set(sampleIndex, NanNew(sample));
  //   sampleIndex++;
  // }

  // NanReturnValue(output);

void Init(Handle<Object> exports){
  exports->Set(NanNew("version"),
    NanNew<FunctionTemplate>(version)->GetFunction());

  exports->Set(NanNew("sineGenerate"),
    NanNew<FunctionTemplate>(sineGenerate)->GetFunction());
}

NODE_MODULE(NtCpp, Init);