#include "wrapped/timout.h"
#include "wrapped/spice.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}


Napi::Value timout(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if(info.Length() == 2 && info[0].IsNumber() && info[1].IsString()){
    const SpiceDouble et = info[0].As<Napi::Number>().DoubleValue();
    const std::string pictur_str = info[1].As<Napi::String>().Utf8Value();
    const ConstSpiceChar* pictur = pictur_str.c_str();
    SpiceChar output[256];

    timout_c(et, pictur, 255, output);
    
    // enforce a null terminator
    output[255] = '\0';

    if(ErrorCheck(env)){
      return env.Null();
    }           

    return Napi::String::New(env, output);
  }
  
  Napi::TypeError::New(env, "timout expected input (et, pictur) where et is numerical time (seconds past J2000) and pictur is a format specification for the output string.  See NAIF SPICE docs for 'timout'.").ThrowAsJavaScriptException();    
  return env.Null();
}
