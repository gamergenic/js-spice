#include "twopi.h"
#include "spice.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}

Napi::Value twopi(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if(info.Length() == 0){
    return Napi::Number::New(env, twopi_c());
  }

  Napi::TypeError::New(env, "twopi expected no argument").ThrowAsJavaScriptException();    
  return env.Null();
}
