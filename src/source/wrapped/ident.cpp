// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/ident.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"


Napi::Value ident(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble matrix[3][3];
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/ident_c.html
    ident_c(matrix);

    return Pack(info).mat(matrix).nocheck(); 
}
