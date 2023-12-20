#include "ephemeris_time.h"
#include "ephemeris_period.h"
#include "spice.h"
#include <napi.h>
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include <string>
#include <cmath>
#include <iostream>

Napi::FunctionReference EphemerisTime::constructor;

Napi::Object EphemerisTime::Init(Napi::Env env, Napi::Object exports) {

    Napi::Function func = DefineClass(env, "EphemerisTime", {
        InstanceMethod("toString", &EphemerisTime::ToString),
        InstanceMethod("toJSON", &EphemerisTime::ToJson),

        InstanceMethod("getEt", &EphemerisTime::GetEt),

        InstanceMethod("setEt", &EphemerisTime::SetEt),
        InstanceMethod("setString", &EphemerisTime::SetString),

        InstanceMethod("add", &EphemerisTime::Add),
        InstanceMethod("subtract", &EphemerisTime::Subtract),

        StaticMethod("isA", &EphemerisTime::IsA),
        StaticMethod("fromJson", &EphemerisTime::FromJson),
       
        StaticMethod("fromEt", &EphemerisTime::FromEt),
        StaticMethod("fromString", &EphemerisTime::FromString),
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("EphemerisTime", func);
    // env.SetInstanceData(constructor);

    return exports;
}

EphemerisTime::EphemerisTime(const Napi::CallbackInfo& info) : Napi::ObjectWrap<EphemerisTime>(info) {
    et = j2000_c();
    if(info.Length() == 1 && CanConvert(info[0])){
        et = ConvertValue(info[0]);
    }
}

Napi::Object EphemerisTime::NewInstance(Napi::Env env, Napi::Value arg) {
    Napi::EscapableHandleScope scope(env);
    Napi::Object obj = constructor.New({ arg });
    return scope.Escape(napi_value(obj)).ToObject();
}

Napi::Value EphemerisTime::IsA(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(info.Length() == 1){
        bool bIsA = IsInstanceOf(info[0]);
        return Napi::Boolean::New(env, bIsA);
    }

    Napi::TypeError::New(env, "requires 1 arg").ThrowAsJavaScriptException();
    return env.Null();
}

bool EphemerisTime::IsInstanceOf(Napi::Value value){
    if(!value.IsObject()){
        return false;
    }

    Napi::Object obj = value.As<Napi::Object>();
    Napi::Function ephemerisTimeConstructor = GetConstructor(value.Env());

    bool isInstanceOfEphemerisTime = false;
    napi_status status = napi_instanceof(value.Env(), obj, ephemerisTimeConstructor, &isInstanceOfEphemerisTime);

    return status == napi_ok && isInstanceOfEphemerisTime;
}

bool EphemerisTime::IsObject(Napi::Value value){
    Napi::Env env = value.Env();
    Napi::HandleScope scope(env);

    if(IsInstanceOf(value)) return true;

    if(value.IsObject()){
        Napi::Object obj = value.As<Napi::Object>();
        if(obj.HasOwnProperty("et") && obj.Get("et").IsNumber()) return true;
    }

    return false;
}

bool EphemerisTime::CanConvert(Napi::Value value){
    Napi::Env env = value.Env();
    Napi::HandleScope scope(env);

    if(value.IsNumber()) return true;
    if(IsObject(value)) return true;

    return false;
}

double EphemerisTime::ConvertValue(Napi::Value value){
    Napi::Env env = value.Env();
    Napi::HandleScope scope(env);

    if(value.IsNumber()){
        return value.As<Napi::Number>().DoubleValue();
    }

    if(value.IsObject()){
        Napi::Object obj = value.As<Napi::Object>();

        if(IsInstanceOf(obj)){
            EphemerisTime* rhs = Napi::ObjectWrap<EphemerisTime>::Unwrap(obj);
            return rhs->et;
        }

        if(obj.HasOwnProperty("et")){
            Napi::Value etValue = obj.Get("et");
            if(etValue.IsNumber()){
                return etValue.As<Napi::Number>().DoubleValue();
            }
        }
    }

    return 0;
}


Napi::Value EphemerisTime::ToString(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(info.Length() > 2){
      Napi::TypeError::New(env, "expected (et2utc_format_string, precision)").ThrowAsJavaScriptException();
      return env.Null();
    }

    if(info.Length() == 0){
      std::string etStr = std::to_string(et);      
      return Napi::String::New(env, etStr);
    }

    ConstSpiceChar* format = nullptr;      
    SpiceInt prec = 0;
    SpiceInt utclen = 128;
    SpiceChar utcstr[128];
    utcstr[0] = '\0';

    if(!info[0].IsString()){
      Napi::TypeError::New(env, "expected format string").ThrowAsJavaScriptException();
      return env.Null();
    }

    if(info.Length() > 1 && !info[1].IsNumber()){
      Napi::TypeError::New(env, "expected precision number").ThrowAsJavaScriptException();
      return env.Null();
    }

    if(info.Length() > 1){
      prec = (SpiceInt)info[1].As<Napi::Number>().Int32Value();
    }

    std::string format_str = info[0].As<Napi::String>().Utf8Value();
    format = format_str.c_str();      

    et2utc_c ( et, format, prec, utclen, utcstr);
    std::string etString = std::string(utcstr);

    return Napi::String::New(env, etString);
}

Napi::Value EphemerisTime::ToJson(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    Napi::Object obj = Napi::Object::New(env);

    obj.Set("et", Napi::Number::New(env, this->et));

    return obj;  
}

Napi::Value EphemerisTime::FromJson(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(info.Length() != 1){
        Napi::TypeError::New(env, "expected one value for et").ThrowAsJavaScriptException();
        return env.Null();
    }        

    if (info[0].IsObject()) {

        Napi::Object obj = info[0].As<Napi::Object>();
        if (!obj.HasOwnProperty("et")) {
            Napi::TypeError::New(env, "et property is missing").ThrowAsJavaScriptException();
            return env.Null();
        }

        Napi::Value etValue = obj.Get("et");
        if (!etValue.IsNumber()) {
            Napi::TypeError::New(env, "et must be a number").ThrowAsJavaScriptException();
            return env.Null();
        }

        return NewInstance(env, etValue);
    }

    if(info[0].IsNumber()){
        return NewInstance(env, info[0]);
    }

    Napi::TypeError::New(env, "et must be an object with et property, or number").ThrowAsJavaScriptException();
    return env.Null();        
}

Napi::Value EphemerisTime::GetEt(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::Number::New(env, et);  
}


Napi::Value EphemerisTime::FromEt(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(info.Length() != 1 || !info[0].IsNumber()){
        Napi::TypeError::New(env, "expected one numerical value").ThrowAsJavaScriptException();
        return env.Null();
    }        

    return NewInstance(env, info[0]);
}


Napi::Value EphemerisTime::FromString(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(info.Length() == 1 && info[0].IsString()){

      std::string time_str = info[0].As<Napi::String>().Utf8Value();
      const ConstSpiceChar* time = time_str.c_str();

      double et = 0;
      str2et_c(time, &et);

      if(!ErrorCheck(env)){
        return NewInstance(env, Napi::Number::New(env, et));
      }      
    } else {
        Napi::TypeError::New(env, "Number expected or time string").ThrowAsJavaScriptException();
        return env.Null();
    }
    return env.Null();
}


Napi::Value EphemerisTime::SetEt(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    
    if (info.Length() == 1 && info[0].IsNumber()) {
 
        et = info[0].As<Napi::Number>().DoubleValue();
 
    } else {
        Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
    }
    return env.Null();
}

Napi::Value EphemerisTime::SetString(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    
    if(info.Length() == 1 && info[0].IsString()){

      std::string time_str = info[0].As<Napi::String>().Utf8Value();
      const ConstSpiceChar* time = time_str.c_str();

      str2et_c(time, &et);

      ErrorCheck(env);

    } else {
        Napi::TypeError::New(env, "String expected").ThrowAsJavaScriptException();
    }       
    return env.Null();
}

Napi::Value EphemerisTime::Add(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    
    if(info.Length() == 1){
        Napi::Value result;
        if(Add(result, *this, info[0])) return result;
    }

    Napi::TypeError::New(env, "requires 1 arg: must be EphemerisPeriod, { dt: }, or number").ThrowAsJavaScriptException();
    return env.Null();
}

Napi::Value EphemerisTime::Subtract(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(info.Length() == 1){
        Napi::Value result;
        if(Subtract(result, *this, info[0])) return result;
    }

    Napi::TypeError::New(env, "requires 1 arg: must be EphemerisTime, EphemerisPeriod, {et: }, { dt: }, or number").ThrowAsJavaScriptException();
    return env.Null();
}



bool EphemerisTime::Add(Napi::Value& out, const EphemerisTime& lhs, const Napi::Value& rhs){
    Napi::Env env = lhs.Env();
    Napi::HandleScope scope(env);

    // Add a number, interpreted as seconds?
    bool bCanConvert = EphemerisPeriod::CanConvert(rhs);
    if(bCanConvert){
        out = NewInstance(env, Napi::Number::New(env, lhs.et + EphemerisPeriod::ConvertValue(rhs)));
    }

    return bCanConvert;
}

bool EphemerisTime::Subtract(Napi::Value& out, const EphemerisTime& lhs, const Napi::Value& rhs){
    Napi::Env env = lhs.Env();
    Napi::HandleScope scope(env);

    // Subtract a number, interpreted as seconds?
    const bool bCanConvertFromDt =  EphemerisPeriod::CanConvert(rhs);
    if(bCanConvertFromDt){
        out = NewInstance(env, Napi::Number::New(env, lhs.et - EphemerisPeriod::ConvertValue(rhs)));
    }
    const bool bCanConvertFromEt =  !bCanConvertFromDt && CanConvert(rhs);
    if(bCanConvertFromEt){
        out = EphemerisPeriod::NewInstance(env, Napi::Number::New(env, lhs.et - ConvertValue(rhs)));
    }

    return bCanConvertFromDt || bCanConvertFromEt;
}

