// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/vzero.h"
extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value vzero(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble v[3];
    if(
      Unpack("vzero", info)
      .rec(v, "v")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vzero_c.html
    SpiceBoolean flag = vzero_c(v);

    return Pack(info).flag(flag).nocheck(); 
}
