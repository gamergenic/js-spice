// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/spkcpt.h"
#include "utility/err.h"

extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value spkcpt(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble et, trgpos[3];
    std::string trgctr, trgref, outref, refloc, abcorr, obsrvr;
    if(
      Unpack("spkcpt", info)
      .rec(trgpos, "trgpos")
      .str(trgctr, "trgctr")
      .str(trgref, "trgref")
      .et(et)
      .str(outref, "outref")
      .str(refloc, "refloc")
      .str(abcorr, "abcorr")
      .str(obsrvr, "obsrvr")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble     state[6];
    SpiceDouble     lt;
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkcpt_c.html
    spkcpt_c(trgpos, trgctr.c_str(), trgref.c_str(), et, outref.c_str(), refloc.c_str(), abcorr.c_str(), obsrvr.c_str(), state, &lt);

    return Pack(info).state(state).as("state").with(lt, "lt").check();
}
