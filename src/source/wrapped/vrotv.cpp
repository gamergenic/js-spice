// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/vrotv.h"
extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value vrotv(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble v[3], axis[3], theta;
    if(
      Unpack("vrotv", info)
      .rec(v, "v")
      .rec(axis, "axis")
      .d(theta, "theta")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vrotv_c.html
    SpiceDouble r[3];
    vrotv_c(v, axis, theta, r);

    return Pack(info).rec(r).nocheck(); 
}
