#include "recpgr.h"
#include "spice.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}

Napi::Value recpgr(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if(info.Length() == 4 || info.Length() == 6){

    std::string body_str;
    if(info[0].IsString()){
        body_str = info[0].ToString().Utf8Value();            
    }
    else {
        Napi::TypeError::New(env, "recpgr expected (body, [x, y, z], re, f)").ThrowAsJavaScriptException();    
        return env.Null();
    }
    ConstSpiceChar* body = body_str.c_str();     

    std::vector<Napi::Value> input = std::vector<Napi::Value>({ info[1] });
    if(info.Length() == 6){
      input.push_back(info[2]);
      input.push_back(info[3]);
    }

    Napi::Value reValue = info.Length() == 6 ? info[4] : info[2];
    if(!reValue.IsNumber()){
      Napi::TypeError::New(env, "recpgr expected (body, [x, y, z], re, f) where re = numeric Equatorial radius of the reference spheroid in km").ThrowAsJavaScriptException();    
      return env.Null();
    }
    const SpiceDouble re = reValue.As<Napi::Number>().DoubleValue();

    Napi::Value fValue = info.Length() == 6 ? info[5] : info[3];
    if(!fValue.IsNumber()){
      Napi::TypeError::New(env, "recpgr expected (body, [x, y, z], re, f) where f = numeric Flattening coefficient").ThrowAsJavaScriptException();    
      return env.Null();
    }
    const SpiceDouble f = fValue.As<Napi::Number>().DoubleValue();

    SpiceDouble rectan[3];
    if(ExtractRecVector(input, rectan))
    {
        SpiceDouble lon, lat, alt;
        recpgr_c(body, rectan, re, f, &lon, &lat, &alt);

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

  Napi::TypeError::New(env, "recpgr expected (body, [x, y, z], re, f)").ThrowAsJavaScriptException();    
  return env.Null();
}
