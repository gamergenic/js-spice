// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/pgrrec.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value pgrrec(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble radius, lon, lat, re, f;
    std::string body_str;            
    if(
      Unpack("pgrrec", info)
      .str(body_str, "body")
      .pgr(radius, lon, lat)
      .d(re, "Re equatorial radius of the reference spheroid in km")
      .d(f, "f flattening coefficient")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    ConstSpiceChar* body = body_str.c_str(); 
    SpiceDouble rectan[3];
    pgrrec_c(body, radius, lon, lat, re, f, rectan);
    return Pack(info).rec(rectan).check(); 
}
