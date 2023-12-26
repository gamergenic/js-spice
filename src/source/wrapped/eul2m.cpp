// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/eul2m.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value eul2m(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble angle3, angle2, angle1;
    SpiceInt axis3, axis2, axis1;
    if(
      Unpack("eul2m", info)
      .d(angle3, "angle3")
      .d(angle2, "angle2")
      .d(angle1, "angle1")
      .i(axis3, "axis3")
      .i(axis2, "axis2")
      .i(axis1, "axis1")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble r[3][3];
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/eul2m_c.html
    eul2m_c(angle3, angle2, angle1, axis3, axis2, axis1, r);

    return Pack(info).mat(r).check(); 
}
