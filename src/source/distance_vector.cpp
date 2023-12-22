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
        InstanceMethod("toString", &DistanceVector::ToString),

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

    std::cout << "DistanceVector constructed" << std::endl;

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



Napi::Value DistanceVector::ToString(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);


    if (!x.IsEmpty() && x.Value().IsObject()) {
        Napi::Object xObj = x.Value().As<Napi::Object>();
        if (xObj.Has("toString")) { // Use the correct case for "ToString"
            Napi::Value string = xObj.Get("toString").As<Napi::Function>().Call({});
            // Handle the string value as needed
            std::cout << "LEROY 1" << std::endl;

            if(string.IsString()){
                std::cout << "LEROY 1b" << std::endl;
            } else {
                std::cout << "LEROY 1c" << std::endl;
            }
        } else {
            // Handle the case where "ToString" method is not found
            std::cout << "LEROY 2" << std::endl;
        }
    } else {
        // Handle the case where x is empty or not an object
        std::cout << "LEROY 3" << std::endl;
    }

    if(Distance::IsInstanceOf(x.Value())){
        std::cout << "LEROY JENKINS!!!" << std::endl;
    }

    // Ensure each child (x, y, z) has a valid reference
    if (!x.IsEmpty() && !y.IsEmpty() && !z.IsEmpty()) {
        // Retrieve string representations of x, y, and z

        x.Value();
        std::cout << "1" << std::endl;

        x.Value().As<Napi::Object>();
        std::cout << "2" << std::endl;

        x.Value().As<Napi::Object>().Get("toString");
        std::cout << "3" << std::endl;

        x.Value().As<Napi::Object>().Get("toString").As<Napi::Function>();
        std::cout << "4" << std::endl;

        Napi::Value string = x.Value().As<Napi::Object>().Get("toString").As<Napi::Function>().Call({});
        std::cout << "5" << std::endl;

        if(string.IsString())
        {
            std::string str = string.As<Napi::String>().Utf8Value();
            std::cout << str << std::endl;
        }
        std::cout << "6" << std::endl;


        Napi::Value xString = x.Value().As<Napi::Object>().Get("toString").As<Napi::Function>().Call({});
        Napi::Value yString = y.Value().As<Napi::Object>().Get("toString").As<Napi::Function>().Call({});
        Napi::Value zString = z.Value().As<Napi::Object>().Get("toString").As<Napi::Function>().Call({});

        // Concatenate the string representations with commas
        std::string result = xString.As<Napi::String>().Utf8Value() + ", " +
                             yString.As<Napi::String>().Utf8Value() + ", " +
                             zString.As<Napi::String>().Utf8Value();

        // Return the concatenated string
        return Napi::String::New(env, result);
    } else {
        // Return a default string or handle the error appropriately
        return Napi::String::New(env, "Invalid DistanceVector");
    }
}

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