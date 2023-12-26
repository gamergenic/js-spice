#include "wrapped/spkcpo.h"
#include "utility/err.h"

extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value spkcpo(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    std::string target, outref, refloc, abcorr, obsctr, obsref;
    SpiceDouble et, obspos[3];
    if(
      Unpack("spkcpo", info)
      .str(target, "target")
      .et(et)
      .str(outref, "outref")
      .str(refloc, "refloc")
      .str(abcorr, "abcorr")
      .rec(obspos, "obspos")
      .str(obsctr, "obsctr")
      .str(obsref, "obsref")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble     state[6];
    SpiceDouble     lt;
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkcpo_c.html
    spkcpo_c(target.c_str(), et, outref.c_str(), refloc.c_str(), abcorr.c_str(), obspos, obsctr.c_str(), obsref.c_str(), state, &lt);

    return Pack(info).state(state).as("state").with(lt, "lt").check();
}
