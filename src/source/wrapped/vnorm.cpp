#include "wrapped/vnorm.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value vnorm(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble v1[3];
    if(
      Unpack("vnorm", info)
      .rec(v1)
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vnorm_c.html
    SpiceDouble norm = vnorm_c(v1);

    return Pack(info).d(norm).nocheck(); 
}
