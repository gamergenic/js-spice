#include "latrec.h"
#include "spice.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}

Napi::Value latrec(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if(info.Length() == 1 && info[0].IsObject()){

    Napi::Object input = info[0].As<Napi::Object>();
    if(input.HasOwnProperty("radius") && input.HasOwnProperty("lon") && input.HasOwnProperty("lat")){

      Napi::Value radiusValue = input.Get("radius"), lonValue = input.Get("lon"), latValue = input.Get("lat");
      if(radiusValue.IsNumber() && lonValue.IsNumber() && latValue.IsNumber()){
        SpiceDouble radius = radiusValue.As<Napi::Number>().DoubleValue();
        SpiceDouble lon = lonValue.As<Napi::Number>().DoubleValue();
        SpiceDouble lat = latValue.As<Napi::Number>().DoubleValue();

        SpiceDouble rectan[3];
        latrec_c(radius, lon, lat, rectan);

        Napi::Array result = Napi::Array::New(env, 3);
        result.Set((uint32_t)0, rectan[0]);
        result.Set((uint32_t)1, rectan[1]);
        result.Set((uint32_t)2, rectan[2]);
        return result;
      }
    }
  }

  Napi::TypeError::New(env, "latrec expected object like { radius:0, lon:0, lat:0 }").ThrowAsJavaScriptException();    
  return env.Null();
}
