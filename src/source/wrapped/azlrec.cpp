#include "wrapped/azlrec.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value azlrec(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble range, az, el;
    SpiceBoolean azccw, elplsz;
    if(
      Unpack("azlrec", info)
      .azl(range, az, el)
      .flag(azccw, "azccw")
      .flag(elplsz, "elplsz")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble rectan[3];
    azlrec_c(range, az, el, azccw, elplsz, rectan);

    return Pack(info).rec(rectan).nocheck(); 
}
