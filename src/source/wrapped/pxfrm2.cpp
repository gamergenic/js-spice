#include "wrapped/pxfrm2.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value pxfrm2(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    std::string from, to;
    SpiceDouble etfrom, etto;
    if(
      Unpack("pxfrm2", info)
      .str(from, "from")
      .str(to, "to")
      .d(etfrom, "etfrom")
      .d(etto, "etto")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble rotate[3][3];
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/pxfrm2_c.html
    pxfrm2_c(from.c_str(), to.c_str(), etfrom, etto, rotate);

    return Pack(info).mat(rotate).check(); 
}
