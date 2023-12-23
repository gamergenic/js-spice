#include "spd.h"
#include "spice.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}

Napi::Value spd(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if(info.Length() == 0){
    return Napi::Number::New(env, spd_c());
  }

  Napi::TypeError::New(env, "spd expected no argument").ThrowAsJavaScriptException();    
  return env.Null();
}
