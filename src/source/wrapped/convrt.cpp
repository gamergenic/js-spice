// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

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
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }
    std::cout << "convrt exit" << std::endl;

    const ConstSpiceChar* in = in_str.c_str();
    const ConstSpiceChar* out = out_str.c_str();

    SpiceDouble y {0};
    convrt_c(x, in, out, &y);

    return Pack(info).d(y).check(); 
}
