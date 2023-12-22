#include <napi.h>
#include "furnsh.h"
#include "unload.h"
#include "erract.h"
#include "errdev.h"
#include "errprt.h"
#include "str2et.h"
#include "spkpos.h"
#include "radrec.h"
#include "recrad.h"


Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set("str2et", Napi::Function::New(env, str2et));
  exports.Set("furnsh", Napi::Function::New(env, furnsh));
  exports.Set("unload", Napi::Function::New(env, unload));
  exports.Set("erract", Napi::Function::New(env, erract));
  exports.Set("errdev", Napi::Function::New(env, errdev));
  exports.Set("errprt", Napi::Function::New(env, errprt));
  exports.Set("str2et", Napi::Function::New(env, str2et));
  exports.Set("spkpos", Napi::Function::New(env, spkpos));
  exports.Set("recrad", Napi::Function::New(env, recrad));
  exports.Set("radrec", Napi::Function::New(env, radrec));
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)

#include "spice.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}

bool ErrorCheck(Napi::Env& env)
{
    SpiceBoolean failed = failed_c();

    if(failed)
    {
        char szBuffer[SpiceLongMessageMaxLength];

        szBuffer[0] = '\0';
        getmsg_c("LONG", sizeof(szBuffer), szBuffer);

        if (!strnlen(szBuffer, sizeof(szBuffer)))
        {
            szBuffer[0] = '\0';
            getmsg_c("SHORT", sizeof(szBuffer), szBuffer);
        }

        Napi::Error::New(env, szBuffer).ThrowAsJavaScriptException();
        return true;
    }

    return false;
}

bool ExtractRecVector(std::vector<Napi::Value> values, double result[3]){
  if(values.size() == 1 && values[0].IsArray()){
    const Napi::Array inArray = values[0].As<Napi::Array>();

    bool bIsVectorArray = inArray.Length() == 3;
    if(bIsVectorArray){
      const Napi::Value xValue = inArray.Get((uint32_t)0);       
      const Napi::Value yValue = inArray.Get((uint32_t)1);       
      const Napi::Value zValue = inArray.Get((uint32_t)2);
      bIsVectorArray &= xValue.IsNumber();       
      bIsVectorArray &= yValue.IsNumber();       
      bIsVectorArray &= zValue.IsNumber();       
      if(bIsVectorArray){
        result[0] = xValue.As<Napi::Number>().DoubleValue();
        result[1] = yValue.As<Napi::Number>().DoubleValue();
        result[2] = zValue.As<Napi::Number>().DoubleValue();
        return true;
      }
    }
  }
  else if(values.size() == 1 && values[0].IsObject()) {
    const Napi::Object inObject = values[0].As<Napi::Object>();

    bool bIsVectorObject = true;
    bIsVectorObject &= inObject.HasOwnProperty("x");
    bIsVectorObject &= inObject.HasOwnProperty("y");
    bIsVectorObject &= inObject.HasOwnProperty("z");
    if(bIsVectorObject){
      const Napi::Value xValue = inObject.Get("x");       
      const Napi::Value yValue = inObject.Get("y");       
      const Napi::Value zValue = inObject.Get("z");
      bIsVectorObject &= xValue.IsNumber();       
      bIsVectorObject &= yValue.IsNumber();       
      bIsVectorObject &= zValue.IsNumber();       
      if(bIsVectorObject){
        result[0] = xValue.As<Napi::Number>().DoubleValue();
        result[1] = yValue.As<Napi::Number>().DoubleValue();
        result[2] = zValue.As<Napi::Number>().DoubleValue();
        return bIsVectorObject;
      }
    }
  }
  else if (values.size() == 3){
    if(values[0].IsNumber() && values[1].IsNumber() && values[2].IsNumber()){
      result[0] = values[0].As<Napi::Number>().DoubleValue();
      result[1] = values[1].As<Napi::Number>().DoubleValue();
      result[2] = values[2].As<Napi::Number>().DoubleValue();
      return true;
    }
  }

  return false;
}