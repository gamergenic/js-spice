#include "wrapped/axisar.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value axisar(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble axis[3], angle;
    if(
      Unpack("axisar", info)
      .rec(axis)
      .angle(angle, "angle")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceDouble r[3][3];
    axisar_c(axis, angle, r);

    return Pack(info).mat(r).nocheck(); 
}
