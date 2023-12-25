#include "wrapped/recrad.h"

extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"


Napi::Value recrad(const Napi::CallbackInfo& info) {
    Napi::Env& env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble rectan[3];
    if(
      Unpack("recrad", info)
      .rec(rectan)
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();;
        })){
        return env.Null();
    }

    SpiceDouble range, ra, dec;
    recrad_c(rectan, &range, &ra, &dec);

    return Pack(info).rad(range, ra, dec).nocheck();
}
