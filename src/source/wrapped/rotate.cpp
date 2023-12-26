#include "wrapped/rotate.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value rotate(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble angle;
    SpiceInt iaxis;
    if(
      Unpack("rotate", info)
      .angle(angle, "angle")
      .i(iaxis, "iaxis")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble mout[3][3];
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/rotate_c.html
    rotate_c(angle, iaxis, mout);

    return Pack(info).mat(mout).nocheck(); 
}
