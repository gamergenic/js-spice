// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/errprt.h"

extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}

#include "utility/errfunction.h"


Napi::Value errprt(const Napi::CallbackInfo& info) {
    return errFunction<errprt_c>(info);
}