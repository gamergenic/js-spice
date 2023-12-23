#include "wrapped/pgrrec.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}

Napi::Value pgrrec(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if(info.Length() == 4 && info[0].IsString() && info[1].IsObject()){
    if(info[2].IsNumber() && info[3].IsNumber()){
      SpiceDouble re = info[2].As<Napi::Number>().DoubleValue();
      SpiceDouble f = info[3].As<Napi::Number>().DoubleValue();
      Napi::Object input = info[1].As<Napi::Object>();
      if(input.HasOwnProperty("lon") && input.HasOwnProperty("lat") && input.HasOwnProperty("alt")){

        Napi::Value lonValue = input.Get("lon"), latValue = input.Get("lat"), altValue = input.Get("alt");
        if(lonValue.IsNumber() && latValue.IsNumber() && altValue.IsNumber()){
          SpiceDouble lon = lonValue.As<Napi::Number>().DoubleValue();
          SpiceDouble lat = latValue.As<Napi::Number>().DoubleValue();
          SpiceDouble alt = altValue.As<Napi::Number>().DoubleValue();

          std::string body_str = info[0].ToString().Utf8Value();            
          ConstSpiceChar* body = body_str.c_str(); 

          SpiceDouble rectan[3];
          pgrrec_c(body, lon, lat, alt, re, f, rectan);

          if(ErrorCheck(env)){
            return env.Null();
          }                 

          Napi::Array result = Napi::Array::New(env, 3);
          result.Set((uint32_t)0, rectan[0]);
          result.Set((uint32_t)1, rectan[1]);
          result.Set((uint32_t)2, rectan[2]);
          return result;
        }
      }
    }
  }

  Napi::TypeError::New(env, "pgrrec expected input like (body, { range:0, ra:0, dec:0 }, re, f)").ThrowAsJavaScriptException();    
  return env.Null();
}
