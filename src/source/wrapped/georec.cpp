// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/georec.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value georec(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble lon, lat, alt, re, f;
    if(
      Unpack("georec", info)
      .geo(lon, lat, alt)
      .d(re, "Re equatorial radius of the reference spheroid in km")
      .d(f, "f flattening coefficient")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble rectan[3];
    georec_c(lon, lat, alt, re, f, rectan);

    return Pack(info).rec(rectan).check(); 
}
