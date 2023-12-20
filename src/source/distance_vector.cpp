#include "distance_vector.h"
#include "spice.h"
#include <napi.h>
extern "C" {
  #include <SpiceUsr.h>
}
#include <string>
#include <cmath>
#include <iostream>

Napi::FunctionReference DistanceVector::constructor;

Napi::Object DistanceVector::Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "DistanceVector", {
        InstanceMethod("getX", &DistanceVector::GetX),
        InstanceMethod("getY", &DistanceVector::GetY),
        InstanceMethod("getZ", &DistanceVector::GetZ),

        StaticMethod("isA", &DistanceVector::IsA),
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("DistanceVector", func);
    return exports;
}

DistanceVector::DistanceVector(const Napi::CallbackInfo& info) : Napi::ObjectWrap<DistanceVector>(info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    // Error handling should be done here as necessary
    this->x = Napi::Persistent(Distance::constructor.New({Napi::Number::New(env, 0)}));    
    this->y = Napi::Persistent(Distance::constructor.New({Napi::Number::New(env, 0)}));    
    this->z = Napi::Persistent(Distance::constructor.New({Napi::Number::New(env, 0)}));    
}

Napi::Object DistanceVector::NewInstance(Napi::Env env, Napi::Value arg) {
    Napi::EscapableHandleScope scope(env);
    Napi::Object obj = constructor.New({ arg });
    return scope.Escape(napi_value(obj)).ToObject();
}

Napi::Value DistanceVector::GetX(const Napi::CallbackInfo& info) {
    return this->x.Value();
}

Napi::Value DistanceVector::GetY(const Napi::CallbackInfo& info) {
    return this->y.Value();
}

Napi::Value DistanceVector::GetZ(const Napi::CallbackInfo& info) {
    return this->z.Value();
}


Napi::Value DistanceVector::IsA(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(info.Length() == 1){
        bool bIsA = IsInstanceOf(info[0]);
        return Napi::Boolean::New(env, bIsA);
    }

    Napi::TypeError::New(env, "requires 1 arg").ThrowAsJavaScriptException();
    return env.Null();
}

bool DistanceVector::IsInstanceOf(Napi::Value value){
    if(!value.IsObject()){
        return false;
    }

    Napi::Object obj = value.As<Napi::Object>();
    Napi::Function distanceConstructor = DistanceVector::GetConstructor(value.Env());

    bool isInstanceOfDistance = false;
    napi_status status = napi_instanceof(value.Env(), obj, distanceConstructor, &isInstanceOfDistance);

    return status == napi_ok && isInstanceOfDistance;
}


// Napi::Value DistanceVector::ToString(const Napi::CallbackInfo& info) {
//     Napi::Env env = info.Env();
//     Napi::HandleScope scope(env);

//     if(info.Length() == 0){
//       std::string str = "";
//       return Napi::String::New(env, str);
//     }

//     Napi::TypeError::New(env, "no parameters expected").ThrowAsJavaScriptException();
//     return env.Null();
// }

// Napi::Value DistanceVector::ToJson(const Napi::CallbackInfo& info) {
//     Napi::Env env = info.Env();
//     Napi::HandleScope scope(env);

//     Napi::Object obj = Napi::Object::New(env);

//     obj.Set("x", Napi::Number::New(env, this->x));
//     obj.Set("y", Napi::Number::New(env, this->y));
//     obj.Set("z", Napi::Number::New(env, this->z));

//     return obj;  
// }

// Napi::Value DistanceVector::FromJson(const Napi::CallbackInfo& info) {
//     Napi::Env env = info.Env();
//     Napi::HandleScope scope(env);

//     if(info.Length() != 1){
//         Napi::TypeError::New(env, "expected one value for km").ThrowAsJavaScriptException();
//         return env.Null();
//     }        

//     if (info[0].IsObject()) {

//         Napi::Object obj = info[0].As<Napi::Object>();
//         if (!obj.HasOwnProperty("km")) {
//             Napi::TypeError::New(env, "km property is missing").ThrowAsJavaScriptException();
//             return env.Null();
//         }

//         Napi::Value kmValue = obj.Get("km");
//         if (!kmValue.IsNumber()) {
//             Napi::TypeError::New(env, "km must be a number").ThrowAsJavaScriptException();
//             return env.Null();
//         }

//         return NewInstance(env, kmValue);
//     }

//     if(info[0].IsNumber()){
//         return NewInstance(env, info[0]);
//     }

//     Napi::TypeError::New(env, "km must be an object with km property, or number").ThrowAsJavaScriptException();
//     return env.Null();        
// }