// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/axisar.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value axisar(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble axis[3], angle;
    if(
      Unpack("axisar", info)
      .rec(axis)
      .angle(angle, "angle")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble r[3][3];
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/axisar_c.html
    axisar_c(axis, angle, r);

    return Pack(info).mat(r).nocheck(); 
}
