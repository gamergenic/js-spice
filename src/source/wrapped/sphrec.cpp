#include "wrapped/sphrec.h"

extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}

Napi::Value sphrec(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if(info.Length() == 1 && info[0].IsObject()){

    Napi::Object input = info[0].As<Napi::Object>();
    if(input.HasOwnProperty("r") && input.HasOwnProperty("colat") && input.HasOwnProperty("slon")){

      Napi::Value rValue = input.Get("r"), colatValue = input.Get("colat"), slonValue = input.Get("slon");
      if(rValue.IsNumber() && colatValue.IsNumber() && slonValue.IsNumber()){
        SpiceDouble r = rValue.As<Napi::Number>().DoubleValue();
        SpiceDouble colat = colatValue.As<Napi::Number>().DoubleValue();
        SpiceDouble slon = slonValue.As<Napi::Number>().DoubleValue();

        SpiceDouble rectan[3];
        sphrec_c(r, colat, slon, rectan);

        Napi::Array result = Napi::Array::New(env, 3);
        result.Set((uint32_t)0, rectan[0]);
        result.Set((uint32_t)1, rectan[1]);
        result.Set((uint32_t)2, rectan[2]);
        return result;
      }
    }
  }

  Napi::TypeError::New(env, "sphrec expected object like { r:0, colat:0, slon:0 }").ThrowAsJavaScriptException();    
  return env.Null();
}
