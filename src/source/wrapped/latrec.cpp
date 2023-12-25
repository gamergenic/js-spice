#include "wrapped/latrec.h"

extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value latrec(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble radius, lon, lat;
    if(
      Unpack("latrec", info)
      .lat(radius, lon, lat)
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble rectan[3];
    latrec_c(radius, lon, lat, rectan);

    return Pack(info).rec(rectan).nocheck(); 
}
