#include "ephemeris_period.h"
#include "ephemeris_time.h"
#include "spice.h"
#include <napi.h>
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include <string>
#include <cmath>
#include <iostream>

Napi::FunctionReference EphemerisPeriod::constructor;

Napi::Object EphemerisPeriod::Init(Napi::Env env, Napi::Object exports) {

    Napi::Function func = DefineClass(env, "EphemerisPeriod", {
        InstanceMethod("toString", &EphemerisPeriod::ToString),
        InstanceMethod("toJSON", &EphemerisPeriod::ToJson),
        StaticMethod("fromJson", &EphemerisPeriod::FromJson),

        InstanceMethod("setSeconds", &EphemerisPeriod::SetSeconds),
        InstanceMethod("setMinutes", &EphemerisPeriod::SetMinutes),
        InstanceMethod("setHours", &EphemerisPeriod::SetHours),
        InstanceMethod("settDays", &EphemerisPeriod::SetDays),
        InstanceMethod("setYears", &EphemerisPeriod::SetJulianYears),
        InstanceMethod("setJulianYears", &EphemerisPeriod::SetJulianYears),
        InstanceMethod("setTropicalYears", &EphemerisPeriod::SetTropicalYears),        

        InstanceMethod("add", &EphemerisPeriod::Add),
        InstanceMethod("subtract", &EphemerisPeriod::Subtract),
        InstanceMethod("multiply", &EphemerisPeriod::Multiply),
        InstanceMethod("divide", &EphemerisPeriod::Divide),
        InstanceMethod("mod", &EphemerisPeriod::Mod),

        InstanceMethod("getSeconds", &EphemerisPeriod::GetSeconds),
        InstanceMethod("getMinutes", &EphemerisPeriod::GetMinutes),
        InstanceMethod("getHours", &EphemerisPeriod::GetHours),
        InstanceMethod("getDays", &EphemerisPeriod::GetDays),
        InstanceMethod("getYears", &EphemerisPeriod::GetJulianYears),
        InstanceMethod("getJulianYears", &EphemerisPeriod::GetJulianYears),
        InstanceMethod("getTropicalYears", &EphemerisPeriod::GetTropicalYears),

        StaticMethod("isA", &EphemerisPeriod::IsA),
        StaticMethod("fromSeconds", &EphemerisPeriod::FromSeconds),
        StaticMethod("fromMinutes", &EphemerisPeriod::FromMinutes),
        StaticMethod("fromHours", &EphemerisPeriod::FromHours),
        StaticMethod("fromDays", &EphemerisPeriod::FromDays),
        StaticMethod("fromYears", &EphemerisPeriod::FromJulianYears),
        StaticMethod("fromJulianYears", &EphemerisPeriod::FromJulianYears),
        StaticMethod("fromTropicalYears", &EphemerisPeriod::FromTropicalYears),        
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("EphemerisPeriod", func);
    // env.SetInstanceData(constructor);

    return exports;
}

EphemerisPeriod::EphemerisPeriod(const Napi::CallbackInfo& info) : Napi::ObjectWrap<EphemerisPeriod>(info) {
    dt = 0;
    if(info.Length() == 1 && CanConvert(info[0])){
        dt = ConvertValue(info[0]);
    }
}

Napi::Object EphemerisPeriod::NewInstance(Napi::Env env, Napi::Value arg) {
    Napi::EscapableHandleScope scope(env);
    Napi::Object obj = constructor.New({ arg });
    return scope.Escape(napi_value(obj)).ToObject();
}

Napi::Value EphemerisPeriod::IsA(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(info.Length() == 1){
        bool bIsA = IsInstanceOf(info[0]);
        return Napi::Boolean::New(env, bIsA);
    }

    Napi::TypeError::New(env, "requires 1 arg").ThrowAsJavaScriptException();
    return env.Null();
}

bool EphemerisPeriod::IsInstanceOf(Napi::Value value){
    if(!value.IsObject()){
        return false;
    }

    Napi::Object obj = value.As<Napi::Object>();
    Napi::Function ephemerisPeriodConstructor = GetConstructor(value.Env());

    bool isInstanceOfEphemerisPeriod = false;
    napi_status status = napi_instanceof(value.Env(), obj, ephemerisPeriodConstructor, &isInstanceOfEphemerisPeriod);

    return status == napi_ok && isInstanceOfEphemerisPeriod;
}

bool EphemerisPeriod::IsObject(Napi::Value value){
    Napi::Env env = value.Env();
    Napi::HandleScope scope(env);

    if(IsInstanceOf(value)) return true;

    if(value.IsObject()){
        Napi::Object obj = value.As<Napi::Object>();
        if(obj.HasOwnProperty("dt") && obj.Get("dt").IsNumber()) return true;
    }

    return false;
}

bool EphemerisPeriod::CanConvert(Napi::Value value){
    Napi::Env env = value.Env();
    Napi::HandleScope scope(env);

    if(value.IsNumber()) return true;
    if(IsObject(value)) return true;

    return false;
}

double EphemerisPeriod::ConvertValue(Napi::Value value){
    Napi::Env env = value.Env();
    Napi::HandleScope scope(env);

    if(value.IsNumber()){
        return value.As<Napi::Number>().DoubleValue();
    }

    if(value.IsObject()){
        Napi::Object obj = value.As<Napi::Object>();

        if(IsInstanceOf(obj)){
            EphemerisPeriod* rhs = Napi::ObjectWrap<EphemerisPeriod>::Unwrap(obj);
            return rhs->dt;
        }

        if(obj.HasOwnProperty("dt")){
            Napi::Value etValue = obj.Get("dt");
            if(etValue.IsNumber()){
                return etValue.As<Napi::Number>().DoubleValue();
            }
        }
    }

    return 0;
}

Napi::Value EphemerisPeriod::ToString(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if(info.Length() == 0){
      std::string dtStr = std::to_string(dt);      
      return Napi::String::New(env, dtStr);
    }

    Napi::TypeError::New(env, "no parameters expected").ThrowAsJavaScriptException();
    return env.Null();
}

Napi::Value EphemerisPeriod::ToJson(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Object obj = Napi::Object::New(env);

    obj.Set("dt", Napi::Number::New(env, this->dt));

    return obj;  
}

Napi::Value EphemerisPeriod::FromJson(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if(info.Length() != 1){
      Napi::TypeError::New(env, "expected one value for dt").ThrowAsJavaScriptException();
      return env.Null();
  }        

  if (info[0].IsObject()) {

      Napi::Object obj = info[0].As<Napi::Object>();
      if (!obj.HasOwnProperty("dt")) {
          Napi::TypeError::New(env, "dt property is missing").ThrowAsJavaScriptException();
          return env.Null();
      }

      Napi::Value timeValue = obj.Get("dt");
      if (!timeValue.IsNumber()) {
          Napi::TypeError::New(env, "dt must be a number").ThrowAsJavaScriptException();
          return env.Null();
      }

      return NewInstance(env, timeValue);
  }

  if(info[0].IsNumber()){
    return NewInstance(env, info[0]);
  }

  Napi::TypeError::New(env, "dt must be an object with dt property, or number").ThrowAsJavaScriptException();
  return env.Null();        
}

Napi::Value EphemerisPeriod::GetSeconds(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    return Napi::Number::New(env, this->dt);
}

Napi::Value EphemerisPeriod::GetMinutes(const Napi::CallbackInfo& info){
    return ConvertTo(info, "MINUTES");
}

Napi::Value EphemerisPeriod::GetHours(const Napi::CallbackInfo& info){
    return ConvertTo(info, "HOURS");
}

Napi::Value EphemerisPeriod::GetDays(const Napi::CallbackInfo& info){
    return ConvertTo(info, "DAYS");
}

Napi::Value EphemerisPeriod::GetJulianYears(const Napi::CallbackInfo& info){
    return ConvertTo(info, "JULIAN_YEARS");
}

Napi::Value EphemerisPeriod::GetTropicalYears(const Napi::CallbackInfo& info){
    return ConvertTo(info, "TROPICAL_YEARS");
}

Napi::Number EphemerisPeriod::ConvertTo(const Napi::CallbackInfo& info, const char* outUnits){
    Napi::Env env = info.Env();

    SpiceDouble x = this->dt;
    ConstSpiceChar* in = "SECONDS";
    ConstSpiceChar* out = outUnits;
    SpiceDouble y = 0;

    convrt_c(x, in, out, &y);

    return Napi::Number::New(env, y);
}

Napi::Value EphemerisPeriod::ConvertFrom(const Napi::CallbackInfo& info, const char* inUnits){
    Napi::Env env = info.Env();

    if(info.Length() != 1 || !info[0].IsNumber()){
        Napi::TypeError::New(env, "expected one numerical value").ThrowAsJavaScriptException();
        return env.Null();
    }        


    SpiceDouble x = info[0].As<Napi::Number>().DoubleValue();
    ConstSpiceChar* in = inUnits;
    ConstSpiceChar* out = "SECONDS";
    SpiceDouble y = 0;

    convrt_c(x, in, out, &y);

    return NewInstance(env, Napi::Number::New(env, y));
}

Napi::Value EphemerisPeriod::FromSeconds(const Napi::CallbackInfo& info){
    return ConvertFrom(info, "SECONDS");
}

Napi::Value EphemerisPeriod::FromMinutes(const Napi::CallbackInfo& info){
    return ConvertFrom(info, "MINUTES");
}

Napi::Value EphemerisPeriod::FromHours(const Napi::CallbackInfo& info){
    return ConvertFrom(info, "HOURS");
}

Napi::Value EphemerisPeriod::FromDays(const Napi::CallbackInfo& info){
    return ConvertFrom(info, "DAYS");
}

Napi::Value EphemerisPeriod::FromJulianYears(const Napi::CallbackInfo& info){
    return ConvertFrom(info, "JULIAN_YEARS");
}

Napi::Value EphemerisPeriod::FromTropicalYears(const Napi::CallbackInfo& info){
    return ConvertFrom(info, "TROPICAL_YEARS");
}

Napi::Value EphemerisPeriod::SetFrom(const Napi::CallbackInfo& info, const char* inUnits){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(info.Length() != 1 || !info[0].IsNumber()){
        Napi::TypeError::New(env, "expected one numerical value").ThrowAsJavaScriptException();
        return env.Null();
    }        


    SpiceDouble x = info[0].As<Napi::Number>().DoubleValue();
    ConstSpiceChar* in = inUnits;
    ConstSpiceChar* out = "SECONDS";
    SpiceDouble y = 0;

    convrt_c(x, in, out, &y);

    this->dt = y;

    return env.Null();
}

Napi::Value EphemerisPeriod::SetSeconds(const Napi::CallbackInfo& info){
    return SetFrom(info, "SECONDS");
}

Napi::Value EphemerisPeriod::SetMinutes(const Napi::CallbackInfo& info){
    return SetFrom(info, "MINUTES");
}

Napi::Value EphemerisPeriod::SetHours(const Napi::CallbackInfo& info){
    return SetFrom(info, "HOURS");
}

Napi::Value EphemerisPeriod::SetDays(const Napi::CallbackInfo& info){
    return SetFrom(info, "DAYS");
}

Napi::Value EphemerisPeriod::SetJulianYears(const Napi::CallbackInfo& info){
    return SetFrom(info, "JULIAN_YEARS");
}

Napi::Value EphemerisPeriod::SetTropicalYears(const Napi::CallbackInfo& info){
    return SetFrom(info, "TROPICAL_YEARS");
}

Napi::Value EphemerisPeriod::Add(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    
    if(info.Length() == 1){
        Napi::Value result;
        if(Add(result, *this, info[0])) return result;
    }

    Napi::TypeError::New(env, "requires 1 arg: must be EphemerisPeriod, { dt: }, or number").ThrowAsJavaScriptException();
    return env.Null();
}

Napi::Value EphemerisPeriod::Subtract(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(info.Length() == 1){
        Napi::Value result;
        if(Subtract(result, *this, info[0])) return result;
    }

    Napi::TypeError::New(env, "requires 1 arg: must be EphemerisPeriod, { dt: }, or number").ThrowAsJavaScriptException();
    return env.Null();
}

Napi::Value EphemerisPeriod::Multiply(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(info.Length() == 1){
        Napi::Value result;
        if(Multiply(result, *this, info[0])) return result;
    }

    Napi::TypeError::New(env, "requires 1 arg: must be number").ThrowAsJavaScriptException();
    return env.Null();
}

Napi::Value EphemerisPeriod::Divide(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(info.Length() == 1){
        Napi::Value result;
        if(Divide(result, *this, info[0])) return result;
    }

    Napi::TypeError::New(env, "requires 1 arg: must be non-zero number").ThrowAsJavaScriptException();
    return env.Null();
}


Napi::Value EphemerisPeriod::Mod(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(info.Length() == 1){
        Napi::Value result;
        if(Mod(result, *this, info[0])) return result;
    }

    Napi::TypeError::New(env, "requires 1 arg: must be non-zero number").ThrowAsJavaScriptException();
    return env.Null();
}


bool EphemerisPeriod::Add(Napi::Value& out, const EphemerisPeriod& lhs, const Napi::Value& rhs){
    Napi::Env env = lhs.Env();
    Napi::HandleScope scope(env);

    // Add a number, interpreted as seconds?
    bool bCanConvert = CanConvert(rhs);
    if(bCanConvert){
        out = NewInstance(env, Napi::Number::New(env, lhs.dt + ConvertValue(rhs)));
    }

    return bCanConvert;
}

bool EphemerisPeriod::Subtract(Napi::Value& out, const EphemerisPeriod& lhs, const Napi::Value& rhs){
    Napi::Env env = lhs.Env();
    Napi::HandleScope scope(env);

    // Subtract a number, interpreted as seconds?
    const bool bCanConvert =  CanConvert(rhs);
    if(bCanConvert){
        out = NewInstance(env, Napi::Number::New(env, lhs.dt - ConvertValue(rhs)));
    }

    return bCanConvert;
}

bool EphemerisPeriod::Multiply(Napi::Value& out, const EphemerisPeriod& lhs, const Napi::Value& rhs){
    Napi::Env env = lhs.Env();
    Napi::HandleScope scope(env);

    // Multiply by a number, interpreted as seconds?
    const bool bCan =  rhs.IsNumber();
    if(bCan){
        out = NewInstance(env, Napi::Number::New(env, lhs.dt * rhs.As<Napi::Number>().DoubleValue()));
    }

    return bCan;
}

bool EphemerisPeriod::Divide(Napi::Value& out, const EphemerisPeriod& lhs, const Napi::Value& rhs){
    Napi::Env env = lhs.Env();
    Napi::HandleScope scope(env);

    // Divide by a number, interpreted as seconds?
    const bool bCanUseNumber =  rhs.IsNumber();
    if(bCanUseNumber){
        double divisor = rhs.As<Napi::Number>().DoubleValue();
        if(divisor == 0){
            return false;            
        }
        out = NewInstance(env, Napi::Number::New(env, lhs.dt / divisor));
    }
    const bool bCanConvert =  !bCanUseNumber && CanConvert(rhs);
    if(bCanConvert){
        double divisor = ConvertValue(rhs);
        if(divisor == 0){
            return false;            
        }
        out = Napi::Number::New(env, lhs.dt / divisor);
    }

    return bCanUseNumber || bCanConvert;
}


bool EphemerisPeriod::Mod(Napi::Value& out, const EphemerisPeriod& lhs, const Napi::Value& rhs){
    Napi::Env env = lhs.Env();
    Napi::HandleScope scope(env);

    const bool bCanConvert = CanConvert(rhs);
    if(bCanConvert){
        double divisor = ConvertValue(rhs);
        if(divisor == 0){
            return false;            
        }
        out = Napi::Number::New(env, fmod(lhs.dt, divisor));
    }

    return bCanConvert;
}
