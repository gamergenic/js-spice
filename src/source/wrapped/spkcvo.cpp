// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/spkcvo.h"
#include "utility/err.h"

extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value spkcvo(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    std::string target, outref, refloc, abcorr, obsctr, obsref;
    SpiceDouble et, obssta[6], obsepc;
    if(
      Unpack("spkcvo", info)
      .str(target, "target")
      .et(et)
      .str(outref, "outref")
      .str(refloc, "refloc")
      .str(abcorr, "abcorr")
      .state(obssta, "obssta")
      .d(obsepc, "obsepc")
      .str(obsctr, "obsctr")
      .str(obsref, "obsref")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble     state[6];
    SpiceDouble     lt;
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkcvo_c.html
    spkcvo_c(target.c_str(), et, outref.c_str(), refloc.c_str(), abcorr.c_str(), obssta, obsepc, obsctr.c_str(), obsref.c_str(), state, &lt);

    return Pack(info).state(state).as("state").with(lt, "lt").check();
}
