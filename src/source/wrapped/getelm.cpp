#include "wrapped/getelm.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/pack.h"
#include "utility/unpack.h"
#include "js-spice.h"

Napi::Value getelm(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceInt frstyr;
    std::string line1_str, line2_str;
    if(
      Unpack("getelm", info)
      .i(frstyr, "frstyr")
      .punt([=,&line1_str, &line2_str](Napi::Value Next, Unpacker& Unpacker){
        if(Next.IsArray()){
            Napi::Array array = Next.As<Napi::Array>();
            if(array.Length() == 2 && array.Get((uint32_t)0).IsString() && array.Get((uint32_t)1).IsString()){
                line1_str = array.Get((uint32_t)0).As<Napi::String>().Utf8Value();
                line2_str = array.Get((uint32_t)1).As<Napi::String>().Utf8Value();
                return 1;
            }
        }

        Unpacker.setError("getelem expected array [line1string,line2string] for arg 2");
        return 0;
      })
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    SpiceChar   tle[2*SpiceLongMessageMaxLength];
    SpiceDouble epoch;
    SpiceDouble elems[10];
    strncpy(&tle[0], line1_str.c_str(), SpiceLongMessageMaxLength-1);
    strncpy(&tle[SpiceLongMessageMaxLength], line2_str.c_str(), SpiceLongMessageMaxLength-1);
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vcrss_c.html
    getelm_c(frstyr, SpiceLongMessageMaxLength, tle, &epoch, elems);

    return Pack(info).elms(elems).as("elems").with(epoch, "epoch").check();
}
