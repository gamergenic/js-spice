#include "wrapped/azlrec.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}

Napi::Value azlrec(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if(info.Length() == 3 && info[0].IsObject()){
    if(info[1].IsBoolean() && info[2].IsBoolean()){
      Napi::Object input = info[0].As<Napi::Object>();
      if(input.HasOwnProperty("range") && input.HasOwnProperty("az") && input.HasOwnProperty("el")){

        Napi::Value rangeValue = input.Get("range"), azValue = input.Get("az"), elValue = input.Get("el");
        if(rangeValue.IsNumber() && azValue.IsNumber() && elValue.IsNumber()){
          SpiceDouble range = rangeValue.As<Napi::Number>().DoubleValue();
          SpiceDouble az = azValue.As<Napi::Number>().DoubleValue();
          SpiceDouble el = elValue.As<Napi::Number>().DoubleValue();
          SpiceBoolean azccw = info[1].As<Napi::Boolean>().Value() ? SPICETRUE : SPICEFALSE;
          SpiceBoolean elplsz = info[2].As<Napi::Boolean>().Value() ? SPICETRUE : SPICEFALSE;

          SpiceDouble rectan[3];
          azlrec_c(range, az, el, azccw, elplsz, rectan);

          Napi::Array result = Napi::Array::New(env, 3);
          result.Set((uint32_t)0, rectan[0]);
          result.Set((uint32_t)1, rectan[1]);
          result.Set((uint32_t)2, rectan[2]);
          return result;
        }
      }
    }
  }

  Napi::TypeError::New(env, "azlrec expected input ({ range:0, az:0, el:0 }, azccw, elphsz) where azccw = boolean flag for azimuth +direction and elphsz = boolean flag for elevation +direction").ThrowAsJavaScriptException();    
  return env.Null();
}
