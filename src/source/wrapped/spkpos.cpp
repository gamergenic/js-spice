#include "wrapped/spkpos.h"
#include "utility/err.h"

extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value spkpos(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    std::string targ, ref, abcorr, obs;
    SpiceDouble et;
    if(
      Unpack("vcrss", info)
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

    SpiceDouble     ptarg[3];
    SpiceDouble     lt;
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkpos_c.html
    spkpos_c(targ.c_str(), et, ref.c_str(), abcorr.c_str(), obs.c_str(), ptarg, &lt);

    return Pack(info).rec(ptarg).as("ptarg").with(lt, "lt").check();
}
