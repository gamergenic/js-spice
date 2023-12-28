// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/vminus.h"
extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value vminus(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble v1[3];
    if(
      Unpack("vminus", info)
      .rec(v1)
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble vout[3];
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vminus_c.html
    vminus_c(v1, vout);

    return Pack(info).rec(vout).nocheck(); 
}
