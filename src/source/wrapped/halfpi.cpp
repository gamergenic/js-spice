// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/halfpi.h"

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
