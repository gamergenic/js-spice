// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/rpd.h"

extern "C" {
  #include <SpiceUsr.h>
}

Napi::Value rpd(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if(info.Length() == 0){
    return Napi::Number::New(env, rpd_c());
  }

  Napi::TypeError::New(env, "rpd expected no argument").ThrowAsJavaScriptException();    
  return env.Null();
}
