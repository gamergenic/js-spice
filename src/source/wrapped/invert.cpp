#include "wrapped/invert.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value invert(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble m[3][3];
    if(
      Unpack("invert", info)
      .mat(m)
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble mout[3][3];
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/invert_c.html
    invert_c(m, mout);

    return Pack(info).mat(mout).nocheck(); 
}
