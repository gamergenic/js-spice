#include "wrapped/reccyl.h"

extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"


Napi::Value reccyl(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble rectan[3];
    if(
      Unpack("reccyl", info)
      .rec(rectan)
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();;
        })){
        return env.Null();
    }

    SpiceDouble r, clon, z;
    reccyl_c(rectan, &r, &clon, &z);
    return Pack(info).cyl(r, clon, z).nocheck();
}
