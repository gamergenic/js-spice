#include "wrapped/j2100.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"


Napi::Value j2100(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/j2100_c.html
    ConstSpiceDouble j2100 = j2100_c();

    return Pack(info).d(j2100).nocheck(); 
}
