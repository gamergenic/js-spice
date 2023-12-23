#include "wrapped/cylrec.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}

Napi::Value cylrec(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if(info.Length() == 1 && info[0].IsObject()){

    Napi::Object input = info[0].As<Napi::Object>();
    if(input.HasOwnProperty("r") && input.HasOwnProperty("clon") && input.HasOwnProperty("z")){

      Napi::Value rValue = input.Get("r"), clonValue = input.Get("clon"), zValue = input.Get("z");
      if(rValue.IsNumber() && clonValue.IsNumber() && zValue.IsNumber()){
        SpiceDouble r = rValue.As<Napi::Number>().DoubleValue();
        SpiceDouble clon = clonValue.As<Napi::Number>().DoubleValue();
        SpiceDouble z = zValue.As<Napi::Number>().DoubleValue();

        SpiceDouble rectan[3];
        cylrec_c(r, clon, z, rectan);

        Napi::Array result = Napi::Array::New(env, 3);
        result.Set((uint32_t)0, rectan[0]);
        result.Set((uint32_t)1, rectan[1]);
        result.Set((uint32_t)2, rectan[2]);
        return result;
      }
    }
  }

  Napi::TypeError::New(env, "cylrec expected object like { r:0, clon:0, z:0 }").ThrowAsJavaScriptException();    
  return env.Null();
}
