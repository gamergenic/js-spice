// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/deltet.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value deltet(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble epoch;
    std::string eptype_str;
    if(
      Unpack("deltet", info)
      .d(epoch, "epoch")
      .str(eptype_str, "eptype")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble delta;
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/deltet_c.html
    deltet_c(epoch, eptype_str.c_str(), &delta);

    return Pack(info).d(delta).check(); 
}
