#include "wrapped/reclat.h"
#include "wrapped/spice.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}

Napi::Value reclat(const Napi::CallbackInfo& info) {
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
        SpiceDouble radius, lon, lat;
        reclat_c(rectan, &radius, &lon, &lat);

        Napi::Object result = Napi::Object::New(env);
        result.Set("radius", radius);
        result.Set("lon", lon);
        result.Set("lat", lat);

        return result;
    }
  }

  Napi::TypeError::New(env, "reclat expected 1 input vector").ThrowAsJavaScriptException();    
  return env.Null();
}
