#include "wrapped/qxq.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value qxq(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble q1[4], q2[4];
    if(
      Unpack("qxq", info)
      .q(q1, "q1")
      .q(q2, "q2")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble qout[4];
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/qxq_c.html
    qxq_c(q1, q2, qout);

    return Pack(info).q(qout).nocheck(); 
}
