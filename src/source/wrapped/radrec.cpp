#include "wrapped/radrec.h"

extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}

Napi::Value radrec(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if(info.Length() == 1 && info[0].IsObject()){

    Napi::Object input = info[0].As<Napi::Object>();
    if(input.HasOwnProperty("range") && input.HasOwnProperty("ra") && input.HasOwnProperty("dec")){

      Napi::Value rangeValue = input.Get("range"), raValue = input.Get("ra"), decValue = input.Get("dec");
      if(rangeValue.IsNumber() && raValue.IsNumber() && decValue.IsNumber()){
        SpiceDouble range = rangeValue.As<Napi::Number>().DoubleValue();
        SpiceDouble ra = raValue.As<Napi::Number>().DoubleValue();
        SpiceDouble dec = decValue.As<Napi::Number>().DoubleValue();

        SpiceDouble rectan[3];
        radrec_c(range, ra, dec, rectan);

        Napi::Array result = Napi::Array::New(env, 3);
        result.Set((uint32_t)0, rectan[0]);
        result.Set((uint32_t)1, rectan[1]);
        result.Set((uint32_t)2, rectan[2]);
        return result;
      }
    }
  }

  Napi::TypeError::New(env, "radrec expected object like { range:0, ra:0, dec:0 }").ThrowAsJavaScriptException();    
  return env.Null();
}
