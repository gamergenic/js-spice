// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/recgeo.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"
#include "utility/unpack.h"


Napi::Value recgeo(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble rectan[3], re, f;
    if(
      Unpack("recgeo", info)
      .rec(rectan)
      .d(re, "Re equatorial radius of the reference spheroid in km")
      .d(f, "f flattening coefficient")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();;
        })){
        return env.Null();
    }
    
    SpiceDouble lon, lat, alt;
    recgeo_c(rectan, re, f, &lon, &lat, &alt);
    return Pack(info).geo(lon, lat, alt).check();
}
