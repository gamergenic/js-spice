#include "wrapped/pi.h"

extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}

Napi::Value pi(const Napi::CallbackInfo& info) {
  Napi::Env& env = info.Env();
  Napi::HandleScope scope(env);

  if(info.Length() == 0){
    return Napi::Number::New(env, pi_c());
  }

  Napi::TypeError::New(env, "pi expected no argument").ThrowAsJavaScriptException();    
  return env.Null();
}
