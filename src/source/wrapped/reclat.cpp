// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/reclat.h"

extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"
#include "utility/unpack.h"


Napi::Value reclat(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble rectan[3];
    if(
      Unpack("reclat", info)
      .rec(rectan)
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();;
        })){
        return env.Null();
    }

    SpiceDouble radius, lon, lat;
    reclat_c(rectan, &radius, &lon, &lat);
    return Pack(info).lat(radius, lon, lat).nocheck();
}
