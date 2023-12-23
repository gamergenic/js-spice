#include "wrapped/convrt.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}

Napi::Value convrt(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  Napi::HandleScope scope(env);

  if(info.Length() == 3 && info[1].IsString() && info[2].IsString()){

      const std::string in_str = info[1].As<Napi::String>().Utf8Value();
      const std::string out_str = info[2].As<Napi::String>().Utf8Value();
      
      const ConstSpiceChar* in = in_str.c_str();
      const ConstSpiceChar* out = out_str.c_str();

      if(info[0].IsNumber()){

        SpiceDouble x = info[0].As<Napi::Number>().DoubleValue();
        SpiceDouble y {0};

        convrt_c(x, in, out, &y);
        
        if(ErrorCheck(env)){
            return env.Null();
        }             
        
        return Napi::Number::New(env, y);
      }
      else if (info[0].IsArray()){
          Napi::Array inputArray = info[0].As<Napi::Array>();
          Napi::Array outputArray = Napi::Array::New(env, inputArray.Length());

          for(uint32_t i = 0; i < inputArray.Length(); ++i){
            if(!inputArray.Get(i).IsNumber()){
              Napi::TypeError::New(env, "convrt expected a single numeric value or an array of numeric values").ThrowAsJavaScriptException();    
              return env.Null();
            }

            SpiceDouble x = inputArray.Get(i).As<Napi::Number>().DoubleValue();
            SpiceDouble y {0};

            convrt_c(x, in, out, &y);
            
            if(ErrorCheck(env)){
                return env.Null();
            }

            outputArray.Set(i, y);             
          }
          
          return outputArray;
      }
  }
  
  Napi::TypeError::New(env, "convrt expected (x, in, out) where x = numeric value, in/out = string units.  See NAIF SPICE docs for 'convrt'.").ThrowAsJavaScriptException();    
  return env.Null();
}
