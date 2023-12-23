#include "wrapped/errprt.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}

constexpr SpiceInt SpiceLongMessageMaxLength = 1841;

Napi::Value errprt(const Napi::CallbackInfo& info) {
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
    SpiceInt lislen = SpiceLongMessageMaxLength-1;
    SpiceChar list[SpiceLongMessageMaxLength];
    list[0] = '\0';
    if(info.Length() > 1)
    {
        std::string list_str = info[1].ToString().Utf8Value();
        const ConstSpiceChar* list_input = list_str.c_str();        
        strncpy(list, list_input, SpiceLongMessageMaxLength);
    }
    errprt_c(op, lislen, list);

    return Napi::String::New(env, list);
}
