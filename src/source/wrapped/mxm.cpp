#include "wrapped/mxm.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value mxm(const Napi::CallbackInfo& info) {
    Napi::Env& env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble m1[3][3], m2[3][3];
    if(
      Unpack("mxm", info)
      .mat(m1)
      .mat(m2)
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble mout[3][3];
    mxm_c(m1, m2, mout);

    return Pack(info).mat(mout).nocheck(); 
}
