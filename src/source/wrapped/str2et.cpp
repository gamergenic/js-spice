// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/str2et.h"
#include "utility/err.h"

extern "C" {
  #include <SpiceUsr.h>
}
#include <iostream>
#include <string>

Napi::Value str2et(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  Napi::HandleScope scope(env);

  if(info.Length() == 1 && info[0].IsString()){

      double et = 0;
      const std::string time_str = info[0].As<Napi::String>().Utf8Value();
      const ConstSpiceChar* time = time_str.c_str();

      str2et_c(time, &et);
      if(ErrorCheck(env)){
          return env.Null();
      }             
      return Napi::Number::New(env, et);
  }
  
  Napi::TypeError::New(env, "str2et expected 1 string").ThrowAsJavaScriptException();    
  return env.Null();
}
