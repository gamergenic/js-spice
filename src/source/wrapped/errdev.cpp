// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/errdev.h"

extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}

#include "utility/errfunction.h"

Napi::Value errdev(const Napi::CallbackInfo& info) {
    return errFunction<errdev_c>(info);
}

