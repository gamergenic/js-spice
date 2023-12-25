#include "wrapped/b1950.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"


Napi::Value b1950(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/b1950_c.html
    ConstSpiceDouble b1950 = b1950_c();

    return Pack(info).d(b1950).nocheck(); 
}
