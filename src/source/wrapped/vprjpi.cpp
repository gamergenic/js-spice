// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/vprjpi.h"
extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"
#include "utility/unpack.h"
#include "utility/err.h"

Napi::Value vprjpi(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble vin[3];
    SpicePlane projpl, invpl;
    if(
      Unpack("vprjpi", info)
      .rec(vin, "vin")
      .plane(projpl, "projpl")
      .plane(invpl, "invpl")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vprjpi_c.html
    SpiceDouble vout[3];
    SpiceBoolean found = SPICEFALSE;
    vprjpi_c(vin, &projpl, &invpl, vout, &found);

    if(found){
        return Pack(info).rec(vout).check(); 
    }

    ErrorCheck(env);
    return env.Null();
}
