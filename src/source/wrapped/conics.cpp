// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/conics.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value conics(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble  elts[8], et;
    if(
      Unpack("conics", info)
      .conics(elts)
      .et(et)
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble state[6];
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/conics_c.html
    conics_c(elts, et, state);

    return Pack(info).state(state).check(); 
}
