#include "wrapped/recpgr.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"


Napi::Value recpgr(const Napi::CallbackInfo& info) {
    Napi::Env& env = info.Env();
    Napi::HandleScope scope(env);

    std::string body_str;
    SpiceDouble rectan[3], re, f;
    if(
      Unpack("recpgr", info)
      .str(body_str, "body")
      .rec(rectan)
      .d(re, "Re equatorial radius of the reference spheroid in km")
      .d(f, "f flattening coefficient")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();;
        })){
        return env.Null();
    }
    ConstSpiceChar* body = body_str.c_str();  

    SpiceDouble lon, lat, alt;
    recpgr_c(body, rectan, re, f, &lon, &lat, &alt);
    return Pack(info).pgr(lon, lat, alt).check();
}
