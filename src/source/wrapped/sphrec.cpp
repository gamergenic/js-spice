#include "wrapped/sphrec.h"

extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value sphrec(const Napi::CallbackInfo& info) {

    Napi::Env& env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble r, colat, slon;
    if(
      Unpack("sphrec", info)
      .sph(r, colat, slon)
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble rectan[3];
    sphrec_c(r, colat, slon, rectan);

    return Pack(info).rec(rectan).nocheck();   
}
