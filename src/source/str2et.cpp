#include "str2et.h"
#include "ephemeris_time.h"
#include "spice.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include <iostream>
#include <string>

Napi::Value str2et(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  Napi::HandleScope scope(env);

  double et;

  if(info.Length() == 1 && info[0].IsString()){

        std::string time_str = info[0].As<Napi::String>().Utf8Value();
        const ConstSpiceChar* time = time_str.c_str();

        str2et_c(time, &et);

    if(ErrorCheck(env)){
        return env.Null();
    }             
  } else {
      Napi::TypeError::New(env, "str2et expected 1 string").ThrowAsJavaScriptException();    
      return env.Null();
  }  

  Napi::Object obj = EphemerisTime::NewInstance(env, Napi::Number::New(env, et));

  return obj;
}
