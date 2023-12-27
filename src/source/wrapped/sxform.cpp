// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/sxform.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value sxform(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    std::string from, to;
    SpiceDouble et;
    if(
      Unpack("sxform", info)
      .str(from, "from")
      .str(to, "to")
      .et(et)
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble xform[6][6];
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/sxform_c.html
    sxform_c(from.c_str(), to.c_str(), et, xform);

    return Pack(info).statemat(xform).check(); 
}
