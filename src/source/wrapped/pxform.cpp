#include "wrapped/pxform.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value pxform(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    std::string from, to;
    SpiceDouble et;
    if(
      Unpack("pxform", info)
      .str(from, "from")
      .str(to, "to")
      .et(et)
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble rotate[3][3];
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/pxform_c.html
    pxform_c(from.c_str(), to.c_str(), et, rotate);

    return Pack(info).mat(rotate).check(); 
}
