#include "wrapped/mxv.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value mxv(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble m[3][3], vin[3];
    if(
      Unpack("mxv", info)
      .mat(m)
      .rec(vin)
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble vout[3];
    mxv_c(m, vin, vout);

    return Pack(info).rec(vout).nocheck(); 
}
