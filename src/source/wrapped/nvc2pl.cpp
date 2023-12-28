// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/nvc2pl.h"
extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value nvc2pl(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble normal[3], konst;
    if(
      Unpack("nvc2pl", info)
      .rec(normal, "normal")
      .d(konst, "konst")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpicePlane plane;
    nvc2pl_c(normal, konst, &plane);

    return Pack(info).plane(plane).check(); 
}
