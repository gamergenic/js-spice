// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/vlcom3.h"
extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value vlcom(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble a, v1[3], b, v2[3];
    if(
      Unpack("vlcom", info)
      .d(a, "a")
      .rec(v1, "v1")
      .d(b, "b")
      .rec(v2, "v2")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vlcom_c.html
    SpiceDouble sum[3];
    vlcom_c(a, v1, b, v2, sum);

    return Pack(info).rec(sum).nocheck(); 
}
