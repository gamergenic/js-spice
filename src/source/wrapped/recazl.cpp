#include "wrapped/recazl.h"
#include "wrapped/spice.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}

Napi::Value recazl(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if(info.Length() == 3 || info.Length() == 5){
    std::vector<Napi::Value> input = std::vector<Napi::Value>({ info[0] });
    if(info.Length() == 5){
      input.push_back(info[1]);
      input.push_back(info[2]);
    }
    
    Napi::Value azccwValue = info.Length() == 5 ? info[3] : info[1];
    if(!azccwValue.IsBoolean()){
      Napi::TypeError::New(env, "recazl expected ([x, y, z], azccw, elspsz) where azccw = boolean flag indicating how Azimuth is measured (true = clockwise)").ThrowAsJavaScriptException();    
      return env.Null();
    }
    const SpiceBoolean azccw = azccwValue.As<Napi::Boolean>().Value() ? SPICETRUE : SPICEFALSE;


    Napi::Value elplszValue = info.Length() == 5 ? info[4] : info[2];
    if(!elplszValue.IsBoolean()){
      Napi::TypeError::New(env, "recazl expected ([x, y, z], azccw, elspsz) where elplsz = boolean flag indicating how Elevation is measured (true = increases from XY plane towards Z+)").ThrowAsJavaScriptException();    
      return env.Null();
    }
    const SpiceBoolean elplsz = elplszValue.As<Napi::Boolean>().Value() ? SPICETRUE : SPICEFALSE;


    SpiceDouble rectan[3];
    if(ExtractRecVector(input, rectan))
    {
        SpiceDouble range, az, el;
        recazl_c(rectan, azccw, elplsz, &range, &az, &el);

        Napi::Object result = Napi::Object::New(env);
        result.Set("range", range);
        result.Set("az", az);
        result.Set("el", el);

        return result;
    }
  }

  Napi::TypeError::New(env, "recazl expected ([x, y, z], azccw, elspsz)").ThrowAsJavaScriptException();    
  return env.Null();
}
