#include "wrapped/gfposc.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include <cmath>

Napi::Value gfposc(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  bool bInputIsValid = true;
  bInputIsValid = !(info.Length() < 11 || info.Length() > 12);

  if(bInputIsValid){
    bInputIsValid &= info[0].IsString();
    bInputIsValid &= info[1].IsString();
    bInputIsValid &= info[2].IsString();
    bInputIsValid &= info[3].IsString();
    bInputIsValid &= info[4].IsString();
    bInputIsValid &= info[5].IsString();
    bInputIsValid &= info[6].IsString();
    bInputIsValid &= info[7].IsNumber();
    bInputIsValid &= info[8].IsNumber();
    bInputIsValid &= info[9].IsNumber();
    if(!(info[10].IsArray() && info[10].As<Napi::Array>().Length() > 0)){
      Napi::TypeError::New(env, "gfposc expected (target,frame,abcorr,obsrvr,crdsys,coord,relate,refval,adjust,step,cnfine_array[,nintvls]) where cnfine_array is an array of at least one time interval ([start, end]) values").ThrowAsJavaScriptException();    
      return env.Null();
    }
    if(info.Length() > 11){
      bInputIsValid &= info[11].IsNumber();
    }
  }

  if(!bInputIsValid){
    Napi::TypeError::New(env, "gfposc expected (target,frame,abcorr,obsrvr,crdsys,coord,relate,refval,adjust,step,cnfine_array[,nintvls])").ThrowAsJavaScriptException();    
    return env.Null();
  }

  const std::string target_str = info[0].As<Napi::String>().Utf8Value();
  const std::string frame_str  = info[1].As<Napi::String>().Utf8Value();
  const std::string abcorr_str = info[2].As<Napi::String>().Utf8Value();
  const std::string obsrvr_str = info[3].As<Napi::String>().Utf8Value();
  const std::string crdsys_str = info[4].As<Napi::String>().Utf8Value();
  const std::string coord_str  = info[5].As<Napi::String>().Utf8Value();
  const std::string relate_str = info[6].As<Napi::String>().Utf8Value();

  ConstSpiceChar* target = target_str.c_str();
  ConstSpiceChar* frame  = frame_str.c_str();
  ConstSpiceChar* abcorr = abcorr_str.c_str();
  ConstSpiceChar* obsrvr = obsrvr_str.c_str();
  ConstSpiceChar* crdsys = crdsys_str.c_str();
  ConstSpiceChar* coord  = coord_str.c_str();
  ConstSpiceChar* relate = relate_str.c_str();
  SpiceDouble     refval = info[7].As<Napi::Number>().DoubleValue();
  SpiceDouble     adjust = info[8].As<Napi::Number>().DoubleValue();
  SpiceDouble     step   = info[9].As<Napi::Number>().DoubleValue();

  Napi::Array     cnfine_array = info[10].As<Napi::Array>();
  const int MAXWIN = 200;
  if (2 * cnfine_array.Length() > MAXWIN)
  {
      setmsg_c("[cnfine] Window Segment count = #; maximum allowed value is #");
      errdp_c("#", cnfine_array.Length());
      errdp_c("#", MAXWIN / 2);
      sigerr_c("SPICE(VALUEOUTOFRANGE)");
      ErrorCheck(env);
      return env.Null();
  }

  SPICEDOUBLE_CELL(_cnfine, MAXWIN);
  // Spice Cells are static.  They must reinitialized on every use or they
  // may have data sticking around.
  scard_c(0, &_cnfine);

  double totalWindow {0};
  for(uint32_t i = 0; i < cnfine_array.Length(); ++i){
    Napi::Value val = cnfine_array.Get(i);
    double start, stop;
    if (val.IsArray()){
      Napi::Array arr = val.As<Napi::Array>();

      bool bArrayIsValid = true;
      bArrayIsValid &= arr.Length() == 2;
      if(bArrayIsValid){
        Napi::Value startValue = arr.Get((uint32_t)0);
        Napi::Value stopValue = arr.Get((uint32_t)1);
        bArrayIsValid &= startValue.IsNumber();
        bArrayIsValid &= stopValue.IsNumber();
        if(bArrayIsValid){
          start = startValue.As<Napi::Number>().DoubleValue();
          stop = stopValue.As<Napi::Number>().DoubleValue();
        }
      }
      if(!bArrayIsValid){
        Napi::TypeError::New(env, "gfposc expected confinement window array child array [x, y]").ThrowAsJavaScriptException();    
        return env.Null();
      }
    }
    else if(val.IsObject()){
      Napi::Object obj = val.As<Napi::Object>();
      bool bObjectIsValid = true;
      bObjectIsValid &= obj.HasOwnProperty("start");
      bObjectIsValid &= obj.HasOwnProperty("stop");
      if(bObjectIsValid){
        Napi::Value startValue = obj.Get("start");
        bObjectIsValid &= startValue.IsNumber();
        if(bObjectIsValid){
          start = startValue.As<Napi::Number>().DoubleValue();
        }
      }
      if(bObjectIsValid){
        Napi::Value stopValue = obj.Get("stop");
        bObjectIsValid &= stopValue.IsNumber();
        if(bObjectIsValid){
          stop = stopValue.As<Napi::Number>().DoubleValue();
        }
      }
      if(!bObjectIsValid){
        Napi::TypeError::New(env, "gfposc expected confinement window array member object { start: x, stop: y }").ThrowAsJavaScriptException();    
        return env.Null();
      }
    }
    else {
      Napi::TypeError::New(env, "gfposc expected confinement window array member as object { start: x, stop: y} or array [x, y]").ThrowAsJavaScriptException();    
      return env.Null();
    }
    if(start >= stop){
      Napi::TypeError::New(env, "gfposc expected confinement window start < stop").ThrowAsJavaScriptException();    
      return env.Null();
    }
    wninsd_c(start, stop, &_cnfine);
    totalWindow += stop - start;
  }

  SpiceInt        nintvls = 0;
  if(info.Length() > 11){
    nintvls = info[11].As<Napi::Number>().Int32Value();
  } else {
    int n = cnfine_array.Length();
    double m = totalWindow;
    nintvls = (SpiceInt)std::ceil(2 * n + m / step);
  }


  // Outputs
  SPICEDOUBLE_CELL(_result, MAXWIN);
  scard_c(0, &_result);  

  SpiceCell*      cnfine = &_cnfine;
  SpiceCell*      result = &_result; 

  gfposc_c(target, frame, abcorr, obsrvr, crdsys, coord, relate, refval, adjust, step, nintvls, cnfine, result);

  if(ErrorCheck(env)){
    return env.Null();
  }    

  int resultsCount = wncard_c(result);
  if(resultsCount <= 0){
    return env.Null();
  }

  Napi::Array result_array = Napi::Array::New(env, resultsCount);
  for (int i = 0; i < resultsCount; ++i)
  {
      Napi::Array window = Napi::Array::New(env, 2);
      double et1, et2;
      wnfetd_c(result, i, &et1, &et2);
      window.Set((uint32_t)0, et1);
      window.Set((uint32_t)1, et2);
      result_array.Set((uint32_t)i, window);
  }

  if(ErrorCheck(env)){
    return env.Null();
  }    

  return result_array;
}
