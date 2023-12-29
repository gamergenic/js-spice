// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/vupack.h"
extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value vupack(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble v[3];
    if(
      Unpack("vupack", info)
      .rec(v, "v")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vupack_c.html
    SpiceDouble x, y, z;
    vupack_c(v, &x, &y, &z);

    return Pack(info).d(x).as("x").with(y, "y").with(z, "z").nocheck(); 
}
