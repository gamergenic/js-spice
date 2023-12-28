// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/pl2nvc.h"
extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value pl2nvc(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpicePlane plane;
    if(
      Unpack("pl2nvc", info)
      .plane(plane, "plane")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble normal[3], konst;
    pl2nvc_c(&plane, normal, &konst);

    return Pack(info).rec(normal).as("normal").with(konst, "constant").nocheck(); 
}
