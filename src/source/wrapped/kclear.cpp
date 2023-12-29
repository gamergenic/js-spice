// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/kclear.h"
extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/err.h"

// Mostly, this is used for unit testing.
Napi::Value kclear(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    kclear_c();

    ErrorCheck(env);
    return env.Null();
}
