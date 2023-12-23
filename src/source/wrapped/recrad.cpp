#include "wrapped/recrad.h"
#include "wrapped/spice.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}

Napi::Value recrad(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if(info.Length() == 1 || info.Length() == 3){
    std::vector<Napi::Value> input = std::vector<Napi::Value>({ info[0] });
    if(info.Length() == 3){
      input.push_back(info[1]);
      input.push_back(info[2]);
    }
    SpiceDouble rectan[3];
    if(ExtractRecVector(input, rectan))
    {
        SpiceDouble range, ra, dec;
        recrad_c(rectan, &range, &ra, &dec);

        Napi::Object result = Napi::Object::New(env);
        result.Set("range", range);
        result.Set("ra", ra);
        result.Set("dec", dec);

        return result;
    }
  }

  Napi::TypeError::New(env, "recrad expected 1 input vector").ThrowAsJavaScriptException();    
  return env.Null();
}
