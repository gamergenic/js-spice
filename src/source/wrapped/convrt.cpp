#include "wrapped/convrt.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"
#include <iostream>

Napi::Value convrt(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble x;
    std::string in_str = info[1].As<Napi::String>().Utf8Value();
    std::string out_str = info[2].As<Napi::String>().Utf8Value();
      
    if(
      Unpack("convrt", info)
      .d(x, "x")
      .str(in_str, "in")
      .str(out_str, "out")
      .check( [=](const std::string& error) {
            std::cout << "convrt handle error enter" << std::endl;
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
            std::cout << "convrt handle error exit" << std::endl;
        })){
        std::cout << "convrt exit null" << std::endl;
        return env.Null();
    }
    std::cout << "convrt exit" << std::endl;

    const ConstSpiceChar* in = in_str.c_str();
    const ConstSpiceChar* out = out_str.c_str();

    SpiceDouble y {0};
    convrt_c(x, in, out, &y);

    return Pack(info).d(y).check(); 
}
