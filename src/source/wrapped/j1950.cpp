#include "wrapped/j1950.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"


Napi::Value j1950(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/j1950_c.html
    ConstSpiceDouble j1950 = j1950_c();

    return Pack(info).d(j1950).nocheck(); 
}
