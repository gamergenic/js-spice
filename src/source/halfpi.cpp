#include "halfpi.h"
#include "spice.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}

Napi::Value halfpi(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if(info.Length() == 0){
    return Napi::Number::New(env, halfpi_c());
  }

  Napi::TypeError::New(env, "halfpi expected no argument").ThrowAsJavaScriptException();    
  return env.Null();
}
