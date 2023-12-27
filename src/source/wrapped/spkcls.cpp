// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/spkcls.h"

extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/unpack.h"
#include "utility/err.h"

Napi::Value spkcls(const Napi::CallbackInfo& info) {

    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceInt handle;
    if(
      Unpack("spkcls", info)
      .i(handle, "handle")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    spkcls_c(handle);

    ErrorCheck(env);
    return env.Null();   
}
