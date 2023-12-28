// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/prop2b.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value prop2b(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble gm, pvinit[6], dt;
    if(
      Unpack("prop2b", info)
      .gm(dt)
      .state(pvinit, "pvinit")
      .dt(dt)
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble pvprop[6];
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/prop2b_c.html
    prop2b_c(gm, pvinit, dt, pvprop);

    return Pack(info).state(pvprop).check(); 
}
