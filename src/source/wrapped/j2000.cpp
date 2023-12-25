#include "wrapped/j2000.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"


Napi::Value j2000(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/j2000_c.html
    ConstSpiceDouble j2000 = j2000_c();

    return Pack(info).d(j2000).nocheck(); 
}
