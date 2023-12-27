// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/spkgps.h"
#include "utility/err.h"

extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value spkgps(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceInt targ, obs;
    std::string ref;
    SpiceDouble et;
    if(
      Unpack("spkgps", info)
      .i(targ, "targ")
      .et(et)
      .str(ref, "ref")
      .i(obs, "obs")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble     pos[3];
    SpiceDouble     lt;
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkgps_c.html
    spkgps_c(targ, et, ref.c_str(), obs, pos, &lt);

    return Pack(info).rec(pos).as("pos").with(lt, "lt").check();
}
