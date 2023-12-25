#include "wrapped/dpr.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}

Napi::Value dpr(const Napi::CallbackInfo& info) {
  Napi::Env& env = info.Env();
  Napi::HandleScope scope(env);

  if(info.Length() == 0){
    return Napi::Number::New(env, dpr_c());
  }

  Napi::TypeError::New(env, "dpr expected no argument").ThrowAsJavaScriptException();    
  return env.Null();
}
