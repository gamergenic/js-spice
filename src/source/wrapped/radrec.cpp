#include "wrapped/radrec.h"

extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value radrec(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble range, ra, dec;
    if(
      Unpack("radrec", info)
      .rad(range, ra, dec)
      .check( [&](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble rectan[3];
    radrec_c(range, ra, dec, rectan);

    return Pack(info).rec(rectan).nocheck(); 
}
