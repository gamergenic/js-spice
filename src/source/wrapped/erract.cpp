// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/erract.h"

extern "C" {
    #include <SpiceUsr.h>
}

#include "utility/errfunction.h"

Napi::Value erract(const Napi::CallbackInfo& info) {
    return errFunction<erract_c>(info);
}

