// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/psv2pl.h"
extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value psv2pl(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble point[3], span1[3], span2[3];
    if(
      Unpack("psv2pl", info)
      .rec(point, "point")
      .rec(span1, "span1")
      .rec(span2, "span2")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpicePlane plane;
    psv2pl_c(point, span1, span2, &plane);

    return Pack(info).plane(plane).check(); 
}
