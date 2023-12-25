#include "wrapped/recazl.h"
#include "utility/err.h"

extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"


Napi::Value recazl(const Napi::CallbackInfo& info) {
    Napi::Env& env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble rectan[3];
    SpiceBoolean azccw, elplsz;
    if(
      Unpack("recazl", info)
      .rec(rectan)
      .flag(azccw, "azccw")
      .flag(elplsz, "elplsz")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();;
        })){
        return env.Null();
    }

    SpiceDouble range, az, el;
    recazl_c(rectan, azccw, elplsz, &range, &az, &el);
    return Pack(info).azl(range, az, el).nocheck();
}
