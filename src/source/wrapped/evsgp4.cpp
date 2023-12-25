#include "wrapped/evsgp4.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value evsgp4(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble geophs[8], elems[10], et;
    if(
      Unpack("evsgp4", info)
      .et(et)
      .geophs(geophs)
      .tlelems(elems)
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble state[6];
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/evsgp4_c.html
    evsgp4_c(et, geophs, elems, state);

    return Pack(info).state(state).check(); 
}
