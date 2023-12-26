// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/spkezr.h"
#include "utility/err.h"

extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value spkezr(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    std::string targ, ref, abcorr, obs;
    SpiceDouble et;
    if(
      Unpack("spkezr", info)
      .str(targ, "targ")
      .et(et)
      .str(ref, "ref")
      .str(abcorr, "abcorr")
      .str(obs, "obs")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble     starg[6];
    SpiceDouble     lt;
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkpos_c.html
    spkezr_c(targ.c_str(), et, ref.c_str(), abcorr.c_str(), obs.c_str(), starg, &lt);

    return Pack(info).state(starg).as("starg").with(lt, "lt").check();
}
