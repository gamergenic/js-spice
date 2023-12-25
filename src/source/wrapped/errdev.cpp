#include "wrapped/errdev.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}

#include "js-spice.h"

Napi::Value errdev(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsString()) {
        Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
        return env.Null();
    }


    std::string op_str = info[0].ToString().Utf8Value();
    const ConstSpiceChar* op = op_str.c_str();
    SpiceInt devlen = SpiceLongMessageMaxLength-1;
    SpiceChar device[SpiceLongMessageMaxLength];
    device[0] = '\0';
    if(info.Length() > 1)
    {
        std::string device_str = info[1].ToString().Utf8Value();
        const ConstSpiceChar* device_input = device_str.c_str();        
        strncpy(device, device_input, SpiceLongMessageMaxLength);
    }

    errdev_c(op, devlen, device);

    return Napi::String::New(env, device);
}
