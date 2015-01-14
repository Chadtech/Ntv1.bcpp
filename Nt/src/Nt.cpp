#include <nan.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// For sine function
#include <math.h>


using namespace v8;
using v8::String;

NAN_METHOD(version){
  NanScope();
  const char * ntVersion0 = "ntv1bcpp";
  Local <String> ntVersion1 = NanNew<String>(ntVersion0);
  NanReturnValue(ntVersion1);
}

// Arguments are:
// frequency duration
NAN_METHOD(sineGenerate){
  NanScope();

  float sustain = args[1]->Uint32Value();
  float frequency = args[0]->NumberValue();
  frequency /= 44100;

  Local<Array> output = NanNew<Array>(sustain);

  double pi = 3.14159;
  int maxAmplitude = 32767;

  int sampleIndex = 0;
  while (sampleIndex < sustain){
    short sample = maxAmplitude;
    sample *= sin(pi * frequency * sampleIndex * 2);
    output->Set(sampleIndex, NanNew(sample));
    sampleIndex++;
  }

  NanReturnValue(output);
}

void Init(Handle<Object> exports){
  exports->Set(NanNew("version"),
    NanNew<FunctionTemplate>(version)->GetFunction());

  exports->Set(NanNew("sineGenerate"),
    NanNew<FunctionTemplate>(sineGenerate)->GetFunction());
}

NODE_MODULE(NtCpp, Init);

// NAN_METHOD(d4NkMeM35) {
//   printf("DANK MEMES\n");
//   NanReturnUndefined();
// }

// NAN_METHOD(DANKMEMES){
//   NanScope();
//   v8::String::Utf8Value param1(args[0]->ToString());
//   std::string DANKMEMES = std::string(*param1);
//   const char * xXxDaNkMeMeSxXx = DANKMEMES.c_str();
//   Local <String> DaNkMeMeS = NanNew<String>(xXxDaNkMeMeSxXx);
//   NanReturnValue(DaNkMeMeS);
// }

// void Init(Handle<Object> exports) {
//   exports->Set(NanNew("dAnKmEmEs"), 
//     NanNew<FunctionTemplate>(d4NkMeM35)->GetFunction());

//   exports->Set(NanNew("DANKMEMES"), 
//     NanNew<FunctionTemplate>(DANKMEMES)->GetFunction());
// }

// // This --------v has to be the same as the binding.gyp target_name
// NODE_MODULE(DANKMEMES, Init); 