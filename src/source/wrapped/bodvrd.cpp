#include "wrapped/bodvrd.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}

Napi::Value bodvrd(const Napi::CallbackInfo& info) {
  Napi::Env& env = info.Env();
  Napi::HandleScope scope(env);

  if(info.Length() >= 2 && info.Length() <= 3){
    const std::string bodynm_str = info[0].As<Napi::String>().Utf8Value();
    const std::string item_str = info[1].As<Napi::String>().Utf8Value();
    SpiceInt maxn = 9;
    if(info.Length() > 2){
      if(info[2].IsNumber()){
        maxn = info[2].As<Napi::Number>().Int32Value();
      }
      else {
        Napi::TypeError::New(env, "bodvrd expected (bodynm, item [, maxn]) where maxn = integral, max values expected").ThrowAsJavaScriptException();    
        return env.Null();
      }
    }

    const ConstSpiceChar* bodynm = bodynm_str.c_str();
    const ConstSpiceChar* item = item_str.c_str();
    SpiceInt dim;
    std::vector<SpiceDouble> values = std::vector<SpiceDouble>(maxn, 0.);
    bodvrd_c(bodynm, item, maxn, &dim, &values[0]);

    if(ErrorCheck(env) || dim <= 0){
      return env.Null();
    }

    if(dim == 1){
      return Napi::Number::New(env, values[0]);
    }

    Napi::Array results = Napi::Array::New(env, dim);

    for(int i = 0; i < dim; ++i){
      results.Set((uint32_t) i, values[i]);
    }

    return results;
  }  

  Napi::TypeError::New(env, "bodvrd expected (bodynm, item [, maxn])").ThrowAsJavaScriptException();    
  return env.Null();
}
