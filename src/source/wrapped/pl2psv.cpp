// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/pl2psv.h"
extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value pl2psv(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpicePlane plane;
    if(
      Unpack("pl2psv", info)
      .plane(plane, "plane")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble point[3], span1[3], span2[3];
    pl2psv_c(&plane, point, span1, span2);

    return Pack(info).rec(point).as("point").with(span1, "span1").with(span2, "span2").nocheck(); 
}
