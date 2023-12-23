#include "wrapped/recgeo.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "js-spice.h"

Napi::Value recgeo(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if(info.Length() == 3 || info.Length() == 5){
    std::vector<Napi::Value> input = std::vector<Napi::Value>({ info[0] });
    if(info.Length() == 5){
      input.push_back(info[1]);
      input.push_back(info[2]);
    }

    Napi::Value reValue = info.Length() == 5 ? info[3] : info[1];
    if(!reValue.IsNumber()){
      Napi::TypeError::New(env, "recgeo expected ([x, y, z], re, f) where re = numeric Equatorial radius of the reference spheroid in km").ThrowAsJavaScriptException();    
      return env.Null();
    }
    const SpiceDouble re = reValue.As<Napi::Number>().DoubleValue();


    Napi::Value fValue = info.Length() == 5 ? info[4] : info[2];
    if(!fValue.IsNumber()){
      Napi::TypeError::New(env, "recgeo expected ([x, y, z], re, f) where f = numeric Flattening coefficient").ThrowAsJavaScriptException();    
      return env.Null();
    }
    const SpiceDouble f = fValue.As<Napi::Number>().DoubleValue();

    SpiceDouble rectan[3];
    if(ExtractRecVector(input, rectan))
    {
        SpiceDouble lon, lat, alt;
        recgeo_c(rectan, re, f, &lon, &lat, &alt);

        Napi::Object result = Napi::Object::New(env);
        result.Set("lon", lon);
        result.Set("lat", lat);
        result.Set("alt", alt);

        if(ErrorCheck(env)){
          return env.Null();
        }       

        return result;
    }
  }

  Napi::TypeError::New(env, "recgeo expected ([x, y, z], re, f)").ThrowAsJavaScriptException();    
  return env.Null();
}
