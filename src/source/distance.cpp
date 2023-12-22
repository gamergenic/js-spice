#include "distance.h"
#include "spice.h"
#include <napi.h>
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include <string>
#include <cmath>
#include <iostream>

Napi::FunctionReference Distance::constructor;

Napi::Object Distance::Init(Napi::Env env, Napi::Object exports) {

    Napi::Function func = DefineClass(env, "Distance", {
        InstanceMethod("toString", &Distance::ToString),
        InstanceMethod("toJSON", &Distance::ToJson),

        InstanceMethod("getKilometers", &Distance::GetKilometers),
        InstanceMethod("getKm", &Distance::GetKilometers),
        InstanceMethod("getMeters", &Distance::GetMeters),
        InstanceMethod("getCentimeters", &Distance::GetCentimeters),
        InstanceMethod("getMillimeters", &Distance::GetMillimeters),
        InstanceMethod("getFeet", &Distance::GetFeet),
        InstanceMethod("getInches", &Distance::GetInches),
        InstanceMethod("getYards", &Distance::GetYards),
        InstanceMethod("getStatuteMiles", &Distance::GetStatuteMiles),
        InstanceMethod("getNauticalMiles", &Distance::GetNauticalMiles),
        InstanceMethod("getAstronomicalUnits", &Distance::GetAstronomicalUnits),
        InstanceMethod("getAU", &Distance::GetAstronomicalUnits),
        InstanceMethod("getParsecs", &Distance::GetParsecs),
        InstanceMethod("getLightSeconds", &Distance::GetLightSeconds),
        InstanceMethod("getLightYears", &Distance::GetLightYears),

        InstanceMethod("setMeters", &Distance::SetMeters),
        InstanceMethod("setKilometers", &Distance::SetKilometers),
        InstanceMethod("setKm", &Distance::SetKilometers),
        InstanceMethod("setCentimeters", &Distance::SetCentimeters),
        InstanceMethod("setMillimeters", &Distance::SetMillimeters),
        InstanceMethod("setFeet", &Distance::SetFeet),
        InstanceMethod("setInches", &Distance::SetInches),
        InstanceMethod("setYards", &Distance::SetYards),
        InstanceMethod("setStatuteMiles", &Distance::SetStatuteMiles),
        InstanceMethod("setNauticalMiles", &Distance::SetNauticalMiles),
        InstanceMethod("setAstronomicalUnits", &Distance::SetAstronomicalUnits),
        InstanceMethod("setAU", &Distance::SetAstronomicalUnits),
        InstanceMethod("setParsecs", &Distance::SetParsecs),
        InstanceMethod("setLightSeconds", &Distance::SetLightSeconds),
        InstanceMethod("setLightYears", &Distance::SetLightYears),

        InstanceMethod("add", &Distance::Add),
        InstanceMethod("subtract", &Distance::Subtract),
        InstanceMethod("multiply", &Distance::Multiply),
        InstanceMethod("divide", &Distance::Divide),
        InstanceMethod("mod", &Distance::Mod),

        StaticMethod("isA", &Distance::IsA),
        StaticMethod("fromJson", &Distance::FromJson),
        StaticMethod("fromMeters", &Distance::FromMeters),
        StaticMethod("fromKilometers", &Distance::FromKilometers),
        StaticMethod("fromKm", &Distance::FromKilometers),
        StaticMethod("fromCentimeters", &Distance::FromCentimeters),
        StaticMethod("fromMillimeters", &Distance::FromMillimeters),
        StaticMethod("fromFeet", &Distance::FromFeet),
        StaticMethod("fromInches", &Distance::FromInches),
        StaticMethod("fromYards", &Distance::FromYards),
        StaticMethod("fromStatuteMiles", &Distance::FromStatuteMiles),
        StaticMethod("fromNauticalMiles", &Distance::FromNauticalMiles),
        StaticMethod("fromAstronomicalUnits", &Distance::FromAstronomicalUnits),
        StaticMethod("fromAU", &Distance::FromAstronomicalUnits),
        StaticMethod("fromParsecs", &Distance::FromParsecs),
        StaticMethod("fromLightSeconds", &Distance::FromLightSeconds),
        StaticMethod("fromLightYears", &Distance::FromLightYears),
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("Distance", func);
    // env.SetInstanceData(constructor);

    return exports;
}

Distance::Distance(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Distance>(info) {
    km = 0;
    if(info.Length() == 1 && CanConvert(info[0])){
        km = ConvertValue(info[0]);
    }

    std::cout << "Distance constructed" << std::endl;
}

Napi::Object Distance::NewInstance(Napi::Env env, Napi::Value arg) {
    Napi::EscapableHandleScope scope(env);
    Napi::Object obj = constructor.New({ arg });
    return scope.Escape(napi_value(obj)).ToObject();
}

Napi::Value Distance::IsA(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(info.Length() == 1){
        bool bIsA = IsInstanceOf(info[0]);
        return Napi::Boolean::New(env, bIsA);
    }

    Napi::TypeError::New(env, "requires 1 arg").ThrowAsJavaScriptException();
    return env.Null();
}

bool Distance::IsInstanceOf(Napi::Value value){
    if(!value.IsObject()){
        return false;
    }

    Napi::Object obj = value.As<Napi::Object>();
    Napi::Function distanceConstructor = Distance::GetConstructor(value.Env());

    bool isInstanceOfDistance = false;
    napi_status status = napi_instanceof(value.Env(), obj, distanceConstructor, &isInstanceOfDistance);

    return status == napi_ok && isInstanceOfDistance;
}

bool Distance::IsObject(Napi::Value value){
    Napi::Env env = value.Env();
    Napi::HandleScope scope(env);

    if(IsInstanceOf(value)) return true;

    if(value.IsObject()){
        Napi::Object obj = value.As<Napi::Object>();
        if(obj.HasOwnProperty("km") && obj.Get("km").IsNumber()) return true;
    }

    return false;
}

bool Distance::CanConvert(Napi::Value value){
    Napi::Env env = value.Env();
    Napi::HandleScope scope(env);

    if(value.IsNumber()) return true;
    if(IsObject(value)) return true;

    return false;
}

double Distance::ConvertValue(Napi::Value value){
    Napi::Env env = value.Env();
    Napi::HandleScope scope(env);

    if(value.IsNumber()){
        return value.As<Napi::Number>().DoubleValue();
    }

    if(value.IsObject()){
        Napi::Object obj = value.As<Napi::Object>();

        if(IsInstanceOf(obj)){
            Distance* rhs = Napi::ObjectWrap<Distance>::Unwrap(obj);
            return rhs->km;
        }

        if(obj.HasOwnProperty("km")){
            Napi::Value kmValue = obj.Get("km");
            if(kmValue.IsNumber()){
                return kmValue.As<Napi::Number>().DoubleValue();
            }
        }
    }

    return 0;
}


Napi::Value Distance::ToString(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    std::cout << "Distance::ToString!" << std::endl;

    if(info.Length() == 0){
        std::string kmStr = std::to_string(km);      

        std::cout << "Distance::ToString 1" << std::endl;
        return Napi::String::New(env, kmStr);
    }

    std::cout << "Distance::ToString 2" << std::endl;

    Napi::TypeError::New(env, "no parameters expected").ThrowAsJavaScriptException();
    return env.Null();
}

Napi::Value Distance::ToJson(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    Napi::Object obj = Napi::Object::New(env);

    obj.Set("km", Napi::Number::New(env, this->km));

    return obj;  
}

Napi::Value Distance::FromJson(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(info.Length() != 1){
        Napi::TypeError::New(env, "expected one value for km").ThrowAsJavaScriptException();
        return env.Null();
    }        

    if (info[0].IsObject()) {

        Napi::Object obj = info[0].As<Napi::Object>();
        if (!obj.HasOwnProperty("km")) {
            Napi::TypeError::New(env, "km property is missing").ThrowAsJavaScriptException();
            return env.Null();
        }

        Napi::Value kmValue = obj.Get("km");
        if (!kmValue.IsNumber()) {
            Napi::TypeError::New(env, "km must be a number").ThrowAsJavaScriptException();
            return env.Null();
        }

        return NewInstance(env, kmValue);
    }

    if(info[0].IsNumber()){
        return NewInstance(env, info[0]);
    }

    Napi::TypeError::New(env, "km must be an object with km property, or number").ThrowAsJavaScriptException();
    return env.Null();        
}

Napi::Value Distance::GetMeters(const Napi::CallbackInfo& info){
    return ConvertTo(info, "M");
}

Napi::Value Distance::GetKilometers(const Napi::CallbackInfo& info){
    return ConvertTo(info, "KM");
}

Napi::Value Distance::GetCentimeters(const Napi::CallbackInfo& info){
    return ConvertTo(info, "CM");
}

Napi::Value Distance::GetMillimeters(const Napi::CallbackInfo& info){
    return ConvertTo(info, "MM");
}

Napi::Value Distance::GetFeet(const Napi::CallbackInfo& info){
    return ConvertTo(info, "FEET");
}

Napi::Value Distance::GetInches(const Napi::CallbackInfo& info){
    return ConvertTo(info, "INCHES");
}

Napi::Value Distance::GetYards(const Napi::CallbackInfo& info){
    return ConvertTo(info, "YARDS");
}

Napi::Value Distance::GetStatuteMiles(const Napi::CallbackInfo& info){
    return ConvertTo(info, "STATUTE_MILES");
}

Napi::Value Distance::GetNauticalMiles(const Napi::CallbackInfo& info){
    return ConvertTo(info, "NAUTICAL_MILES");
}

Napi::Value Distance::GetAstronomicalUnits(const Napi::CallbackInfo& info){
    return ConvertTo(info, "AU");
}

Napi::Value Distance::GetParsecs(const Napi::CallbackInfo& info){
    return ConvertTo(info, "PARSECS");
}

Napi::Value Distance::GetLightSeconds(const Napi::CallbackInfo& info){
    return ConvertTo(info, "LIGHTSECS");
}

Napi::Value Distance::GetLightYears(const Napi::CallbackInfo& info){
    return ConvertTo(info, "LIGHTYEARS");
}

Napi::Number Distance::ConvertTo(const Napi::CallbackInfo& info, const char* outUnits){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble x = this->km;
    ConstSpiceChar* in = "KM";
    ConstSpiceChar* out = outUnits;
    SpiceDouble y = 0;

    convrt_c(x, in, out, &y);

    return Napi::Number::New(env, y);
}

Napi::Value Distance::ConvertFrom(const Napi::CallbackInfo& info, const char* inUnits){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(info.Length() != 1 || !info[0].IsNumber()){
        Napi::TypeError::New(env, "expected one numerical value").ThrowAsJavaScriptException();
        return env.Null();
    }        


    SpiceDouble x = info[0].As<Napi::Number>().DoubleValue();
    ConstSpiceChar* in = inUnits;
    ConstSpiceChar* out = "KM";
    SpiceDouble y = 0;

    convrt_c(x, in, out, &y);

    return NewInstance(env, Napi::Number::New(env, y));
}


Napi::Value Distance::FromMeters(const Napi::CallbackInfo& info){
    return ConvertFrom(info, "M");
}

Napi::Value Distance::FromKilometers(const Napi::CallbackInfo& info){
    return ConvertFrom(info, "KM");
}

Napi::Value Distance::FromCentimeters(const Napi::CallbackInfo& info){
    return ConvertFrom(info, "CM");
}

Napi::Value Distance::FromMillimeters(const Napi::CallbackInfo& info){
    return ConvertFrom(info, "MM");
}

Napi::Value Distance::FromFeet(const Napi::CallbackInfo& info){
    return ConvertFrom(info, "FEET");
}

Napi::Value Distance::FromInches(const Napi::CallbackInfo& info){
    return ConvertFrom(info, "INCHES");
}

Napi::Value Distance::FromYards(const Napi::CallbackInfo& info){
    return ConvertFrom(info, "YARDS");
}

Napi::Value Distance::FromStatuteMiles(const Napi::CallbackInfo& info){
    return ConvertFrom(info, "STATUTE_MILES");
}

Napi::Value Distance::FromNauticalMiles(const Napi::CallbackInfo& info){
    return ConvertFrom(info, "NAUTICAL_MILES");
}

Napi::Value Distance::FromAstronomicalUnits(const Napi::CallbackInfo& info){
    return ConvertFrom(info, "AU");
}

Napi::Value Distance::FromParsecs(const Napi::CallbackInfo& info){
    return ConvertFrom(info, "PARSECS");
}

Napi::Value Distance::FromLightSeconds(const Napi::CallbackInfo& info){
    return ConvertFrom(info, "LIGHTSECS");
}

Napi::Value Distance::FromLightYears(const Napi::CallbackInfo& info){
    return ConvertFrom(info, "LIGHTYEARS");
}


Napi::Value Distance::SetFrom(const Napi::CallbackInfo& info, const char* inUnits){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(info.Length() != 1 || !info[0].IsNumber()){
        Napi::TypeError::New(env, "expected one numerical value").ThrowAsJavaScriptException();
        return env.Null();
    }        


    SpiceDouble x = info[0].As<Napi::Number>().DoubleValue();
    ConstSpiceChar* in = inUnits;
    ConstSpiceChar* out = "KM";
    SpiceDouble y = 0;

    convrt_c(x, in, out, &y);

    this->km = y;

    return env.Null();
}


Napi::Value Distance::SetMeters(const Napi::CallbackInfo& info){
    return SetFrom(info, "M");
}

Napi::Value Distance::SetKilometers(const Napi::CallbackInfo& info){
    return SetFrom(info, "KM");
}

Napi::Value Distance::SetCentimeters(const Napi::CallbackInfo& info){
    return SetFrom(info, "CM");
}

Napi::Value Distance::SetMillimeters(const Napi::CallbackInfo& info){
    return SetFrom(info, "MM");
}

Napi::Value Distance::SetFeet(const Napi::CallbackInfo& info){
    return SetFrom(info, "FEET");
}

Napi::Value Distance::SetInches(const Napi::CallbackInfo& info){
    return SetFrom(info, "INCHES");
}

Napi::Value Distance::SetYards(const Napi::CallbackInfo& info){
    return SetFrom(info, "YARDS");
}

Napi::Value Distance::SetStatuteMiles(const Napi::CallbackInfo& info){
    return SetFrom(info, "STATUTE_MILES");
}

Napi::Value Distance::SetNauticalMiles(const Napi::CallbackInfo& info){
    return SetFrom(info, "NAUTICAL_MILES");
}

Napi::Value Distance::SetAstronomicalUnits(const Napi::CallbackInfo& info){
    return SetFrom(info, "AU");
}

Napi::Value Distance::SetParsecs(const Napi::CallbackInfo& info){
    return SetFrom(info, "PARSECS");
}

Napi::Value Distance::SetLightSeconds(const Napi::CallbackInfo& info){
    return SetFrom(info, "LIGHTSECS");
}

Napi::Value Distance::SetLightYears(const Napi::CallbackInfo& info){
    return SetFrom(info, "LIGHTYEARS");
}


Napi::Value Distance::Add(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    
    if(info.Length() == 1){
        Napi::Value result;
        if(Add(result, *this, info[0])) return result;
    }

    Napi::TypeError::New(env, "requires 1 arg: must be Distance, { km: }, or number").ThrowAsJavaScriptException();
    return env.Null();
}

Napi::Value Distance::Subtract(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(info.Length() == 1){
        Napi::Value result;
        if(Subtract(result, *this, info[0])) return result;
    }

    Napi::TypeError::New(env, "requires 1 arg: must be Distance, { km: }, or number").ThrowAsJavaScriptException();
    return env.Null();
}

Napi::Value Distance::Multiply(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(info.Length() == 1){
        Napi::Value result;
        if(Multiply(result, *this, info[0])) return result;
    }

    Napi::TypeError::New(env, "requires 1 arg: must be number").ThrowAsJavaScriptException();
    return env.Null();
}

Napi::Value Distance::Divide(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(info.Length() == 1){
        Napi::Value result;
        if(Divide(result, *this, info[0])) return result;
    }    

    Napi::TypeError::New(env, "requires 1 arg: must be non-zero Distance, { km: }, or number").ThrowAsJavaScriptException();
    return env.Null();    
}

Napi::Value Distance::Mod(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(info.Length() == 1){
        Napi::Value result;
        if(Mod(result, *this, info[0])) return result;
    }

    Napi::TypeError::New(env, "requires 1 arg: must be non-zero Distance, { km: }, or number").ThrowAsJavaScriptException();
    return env.Null();
}


bool Distance::Add(Napi::Value& out, const Distance& lhs, const Napi::Value& rhs){
    Napi::Env env = lhs.Env();
    Napi::HandleScope scope(env);

    // Add a number, interpreted as kilometers?
    bool bCanConvert = CanConvert(rhs);
    if(bCanConvert){
        out = NewInstance(env, Napi::Number::New(env, lhs.km + ConvertValue(rhs)));
    }

    return bCanConvert;
}

bool Distance::Subtract(Napi::Value& out, const Distance& lhs, const Napi::Value& rhs){
    Napi::Env env = lhs.Env();
    Napi::HandleScope scope(env);

    // Add a number, interpreted as kilometers?
    bool bCanConvert = CanConvert(rhs);
    if(bCanConvert){
        out = NewInstance(env, Napi::Number::New(env, lhs.km - ConvertValue(rhs)));
    }

    return bCanConvert;
}

bool Distance::Multiply(Napi::Value& out, const Distance& lhs, const Napi::Value& rhs){
    Napi::Env env = lhs.Env();
    Napi::HandleScope scope(env);

    bool bCanMultiply = rhs.IsNumber();

    if(bCanMultiply){
        out = NewInstance(env, Napi::Number::New(env, lhs.km * rhs.As<Napi::Number>().DoubleValue()));
    }

    return bCanMultiply;
}

bool Distance::Divide(Napi::Value& out, const Distance& lhs, const Napi::Value& rhs){
    Napi::Env env = lhs.Env();
    Napi::HandleScope scope(env);

    if(rhs.IsNumber()){
        double divisor = rhs.As<Napi::Number>().DoubleValue();
        if(divisor == 0){
            return false;            
        }               
        out = NewInstance(env, Napi::Number::New(env, lhs.km / divisor));
        return true;
    }
    else if (Distance::IsObject(rhs)){
        double divisor = ConvertValue(rhs);
        if(divisor == 0){
            return false;            
        }               
        out = Napi::Number::New(env, lhs.km / divisor);
        return true;
    }

    return false;
}

bool Distance::Mod(Napi::Value& out, const Distance& lhs, const Napi::Value& rhs){
    Napi::Env env = lhs.Env();
    Napi::HandleScope scope(env);

    bool bCanConvert = CanConvert(rhs);
    if(bCanConvert){
        double divisor = ConvertValue(rhs);
        if(divisor == 0){
            return false;            
        }        
        out = NewInstance(env, Napi::Number::New(env, fmod(lhs.km, divisor)));
    }

    return bCanConvert;    
}
