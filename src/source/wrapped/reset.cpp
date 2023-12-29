// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/reset.h"
extern "C" {
  #include <SpiceUsr.h>
}

// Mostly, this is used for unit testing.
// Wrapped spice functions should detect and reset spice errors then throw
// an exception.
Napi::Value reset(const Napi::CallbackInfo& info) {
    
    // failure is not an option.
    reset_c();

    return info.Env().Null();
}
