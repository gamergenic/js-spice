#include "recsph.h"
#include "spice.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}

Napi::Value recsph(const Napi::CallbackInfo& info) {
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
        SpiceDouble r, colat, slon;
        recsph_c(rectan, &r, &colat, &slon);

        Napi::Object result = Napi::Object::New(env);
        result.Set("r", r);
        result.Set("colat", colat);
        result.Set("slon", slon);

        return result;
    }
  }

  Napi::TypeError::New(env, "recsph expected 1 input vector").ThrowAsJavaScriptException();    
  return env.Null();
}
