// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/twopi.h"

extern "C" {
  #include <SpiceUsr.h>
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
