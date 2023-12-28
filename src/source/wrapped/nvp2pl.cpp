// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/nvp2pl.h"
extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value nvp2pl(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble normal[3], point[3];
    if(
      Unpack("nvp2pl", info)
      .rec(normal, "normal")
      .rec(point, "point")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpicePlane plane;
    nvp2pl_c(normal, point, &plane);

    return Pack(info).plane(plane).check(); 
}
