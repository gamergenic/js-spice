#include "js-spice.h"
#include "utility/pack.h"
extern "C" {
  #include <SpiceUsr.h>
}

// Define a function pointer type for the CSPICE functions
typedef void (*CSpiceFunction)(const ConstSpiceChar*, SpiceInt, SpiceChar[]);

template <CSpiceFunction cspiceFunc>
Napi::Value errFunction(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    bool bInvalidArgs = info.Length() < 1 || info.Length() > 2 || !info[0].IsString();
    bInvalidArgs |= info.Length() == 2 && !info[1].IsString();

    if (bInvalidArgs) {
        Napi::TypeError::New(env, "function expected 1 or 2 string args").ThrowAsJavaScriptException();
        return env.Null();
    }

    std::string op_str = info[0].ToString().Utf8Value();
    const ConstSpiceChar* op = op_str.c_str();
    SpiceInt len = SpiceLongMessageMaxLength-1;
    SpiceChar buffer[SpiceLongMessageMaxLength];

    if(info.Length() > 1) {
        std::string input_str = info[1].ToString().Utf8Value();
        const ConstSpiceChar* input = input_str.c_str();        
        strncpy(buffer, input, len);

        // ensure null-terminated input
        buffer[SpiceLongMessageMaxLength-1] = '\0';
    }

    cspiceFunc(op, len, buffer);

    // ensure null-terminated output
    buffer[SpiceLongMessageMaxLength-1] = '\0';

    return Pack(info).str(buffer).check(); 
}

