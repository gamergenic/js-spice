// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/spkopn.h"

extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value spkopn(const Napi::CallbackInfo& info) {

    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    std::string fname, ifname;
    SpiceInt ncomch;
    if(
      Unpack("spkopn", info)
      .str(fname, "fname")
      .str(ifname, "ifname")
      .i(ncomch, "ncomch")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceInt handle;
    spkopn_c(fname.c_str(), ifname.c_str(), ncomch, &handle);
  
    return Pack(info).i(handle).check();  
}
