#include "wrapped/jyear.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"


Napi::Value jyear(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/jyear_c.html
    ConstSpiceDouble jyear = jyear_c();

    return Pack(info).d(jyear).nocheck(); 
}
