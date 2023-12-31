// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/etcal.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"
#include "js-spice.h"

Napi::Value etcal(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble et;
    if(
      Unpack("etcal", info)
      .et(et)
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/etcal_c.html
    SpiceChar         calstr[SpiceLongMessageMaxLength];
    etcal_c(et, SpiceLongMessageMaxLength, calstr);

    return Pack(info).str(calstr).check(); 
}
