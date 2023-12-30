// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/spkobj.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"
#include "utility/unpack.h"
#include <vector>

Napi::Value spkobj(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    std::string spkfnm;
    if(
      Unpack("spkobj", info)
      .str(spkfnm, "spkobj")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }
    constexpr int MAXOBJ = 1000;

    SPICEINT_CELL(idscell, MAXOBJ);
    // Spice cells are static, so reinitialize.
    scard_c(0, &idscell);

    // Outputs
    SpiceCell* _ids = &idscell;

    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkobj_c.html
    spkobj_c(spkfnm.c_str(), _ids);

    int count = card_c(_ids);
    std::vector<SpiceInt> ids = std::vector<SpiceInt>();
    ids.reserve(count);
    for (int i = 0; i < count; i++)
    {
        SpiceInt id = SPICE_CELL_ELEM_I(_ids, i);
        ids.push_back(int(id));
    }    

    return Pack(info).ints(ids).check();
}
