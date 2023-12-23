#include "erract.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "spice.h"


Napi::Value erract(const Napi::CallbackInfo& info) {
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
    SpiceInt actlen = SpiceLongMessageMaxLength-1;
    SpiceChar action[SpiceLongMessageMaxLength];
    if(info.Length() > 1)
    {
        std::string action_str = info[1].ToString().Utf8Value();
        const ConstSpiceChar* action_input = action_str.c_str();        
        strncpy(action, action_input, SpiceLongMessageMaxLength);
    }


    erract_c(op, actlen, action);

    return Napi::String::New(env, action);
}
