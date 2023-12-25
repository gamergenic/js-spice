#include "wrapped/xpose.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value xpose(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble m1[3][3];
    if(
      Unpack("xpose", info)
      .mat(m1)
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble mout[3][3];
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/xpose_c.html
    xpose_c(m1, mout);

    return Pack(info).mat(mout).nocheck(); 
}
