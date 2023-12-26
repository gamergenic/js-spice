#include "wrapped/m2q.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value m2q(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble r[3][3];
    if(
      Unpack("m2q", info)
      .mat(r, "r")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble q[4];
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/m2q_c.html
    m2q_c(r, q);

    return Pack(info).q(q).check(); 
}
