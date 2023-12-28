// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/vsep.h"
extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value vsep(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble v1[3], v2[3];
    if(
      Unpack("vsep", info)
      .rec(v1, "v1")
      .rec(v2, "v2")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vsep_c.html
    SpiceDouble d = vsep_c(v1, v2);

    return Pack(info).d(d).nocheck(); 
}
