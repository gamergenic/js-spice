#include <napi.h>
#include "azlrec.h"
#include "bodvrd.h"
#include "convrt.h"
#include "cylrec.h"
#include "dpr.h"
#include "erract.h"
#include "errdev.h"
#include "errprt.h"
#include "furnsh.h"
#include "georec.h"
#include "gfposc.h"
#include "halfpi.h"
#include "latrec.h"
#include "pgrrec.h"
#include "pi.h"
#include "rpd.h"
#include "str2et.h"
#include "spd.h"
#include "sphrec.h"
#include "spkpos.h"
#include "timout.h"
#include "radrec.h"
#include "recazl.h"
#include "reccyl.h"
#include "recgeo.h"
#include "reclat.h"
#include "recpgr.h"
#include "recrad.h"
#include "recsph.h"
#include "twopi.h"
#include "unload.h"

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set("azlrec", Napi::Function::New(env, azlrec));
  exports.Set("bodvrd", Napi::Function::New(env, bodvrd));
  exports.Set("convrt", Napi::Function::New(env, convrt));
  exports.Set("cylrec", Napi::Function::New(env, cylrec));
  exports.Set("dpr",    Napi::Function::New(env, dpr));
  exports.Set("erract", Napi::Function::New(env, erract));
  exports.Set("errdev", Napi::Function::New(env, errdev));
  exports.Set("errprt", Napi::Function::New(env, errprt));
  exports.Set("furnsh", Napi::Function::New(env, furnsh));
  exports.Set("georec", Napi::Function::New(env, georec));
  exports.Set("gfposc", Napi::Function::New(env, gfposc));
  exports.Set("halfpi", Napi::Function::New(env, halfpi));
  exports.Set("latrec", Napi::Function::New(env, latrec));
  exports.Set("pgrrec", Napi::Function::New(env, pgrrec));
  exports.Set("pi",     Napi::Function::New(env, pi));
  exports.Set("radrec", Napi::Function::New(env, radrec));
  exports.Set("recazl", Napi::Function::New(env, recazl));
  exports.Set("reccyl", Napi::Function::New(env, reccyl));
  exports.Set("recgeo", Napi::Function::New(env, recgeo));
  exports.Set("reclat", Napi::Function::New(env, reclat));
  exports.Set("recpgr", Napi::Function::New(env, recpgr));
  exports.Set("recrad", Napi::Function::New(env, recrad));
  exports.Set("recsph", Napi::Function::New(env, recsph));
  exports.Set("rpd",    Napi::Function::New(env, rpd));
  exports.Set("str2et", Napi::Function::New(env, str2et));
  exports.Set("spd",    Napi::Function::New(env, spd));
  exports.Set("sphrec", Napi::Function::New(env, sphrec));
  exports.Set("spkpos", Napi::Function::New(env, spkpos));
  exports.Set("timout", Napi::Function::New(env, timout));
  exports.Set("twopi",  Napi::Function::New(env, twopi));
  exports.Set("unload", Napi::Function::New(env, unload));
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