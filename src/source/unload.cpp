#include "unload.h"
#include "spice.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}

Napi::Value unload(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsString()) {
        Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
        return env.Null();
    }

    std::string kernel_str = info[0].ToString().Utf8Value();
    const ConstSpiceChar* kernel = kernel_str.c_str();    

    unload_c(kernel);

    if(ErrorCheck(env)){
        return env.Null();
    }

    return env.Null();
}
