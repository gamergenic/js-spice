#include "wrapped/et2utc.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"
#include "js-spice.h"

Napi::Value et2utc(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble et;
    std::string format;
    SpiceInt    prec;
    if(
      Unpack("et2utc", info)
      .et(et)
      .str(format, "format")
      .i(prec, "prec")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceChar utcstr[SpiceLongMessageMaxLength];
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/et2utc_c.html
    et2utc_c(et, format.c_str(), prec, SpiceLongMessageMaxLength, utcstr);

    return Pack(info).str(utcstr).check(); 
}
