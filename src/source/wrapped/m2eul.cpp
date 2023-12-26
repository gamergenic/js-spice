#include "wrapped/m2eul.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value m2eul(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble r[3][3];
    SpiceInt axis3, axis2, axis1;
    if(
      Unpack("m2eul", info)
      .mat(r, "r")
      .i(axis3, "axis3")
      .i(axis2, "axis2")
      .i(axis1, "axis1")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble angle3, angle2, angle1;
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/m2eul_c.html
    m2eul_c(r, axis3, axis2, axis1, &angle3, &angle2, &angle1);

    return Pack(info).d(angle3).as("angle3").with(angle2, "angle2").with(angle1, "angle1").check(); 
}
