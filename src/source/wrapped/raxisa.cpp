#include "wrapped/raxisa.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value raxisa(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble matrix[3][3];
    if(
      Unpack("raxisa", info)
      .mat(matrix, "matrix")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble angle, axis[3];
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/raxisa_c.html
    raxisa_c(matrix, axis, &angle);

    return Pack(info).rec(axis).as("axis").with(angle, "angle").check(); 
}
