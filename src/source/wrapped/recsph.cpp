#include "wrapped/recsph.h"

extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"


Napi::Value recsph(const Napi::CallbackInfo& info) {
    Napi::Env& env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble rectan[3];
    if(
      Unpack("recsph", info)
      .rec(rectan)
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();;
        })){
        return env.Null();
    }

    SpiceDouble r, colat, slon;
    recsph_c(rectan, &r, &colat, &slon);

    return Pack(info).sph(r, colat, slon).nocheck();
}
