#ifndef _DISTANCE_VECTOR_
#define _DISTANCE_VECTOR_

#include <napi.h>
#include "distance.h"

class DistanceVector : public Napi::ObjectWrap<DistanceVector> {
public:
    explicit DistanceVector(const Napi::CallbackInfo& info);
    
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Object NewInstance(Napi::Env env, Napi::Value arg);
    static Napi::Function GetConstructor(Napi::Env env) {
        return constructor.Value();
    }

    Napi::Value GetX(const Napi::CallbackInfo& info);
    Napi::Value GetY(const Napi::CallbackInfo& info);
    Napi::Value GetZ(const Napi::CallbackInfo& info);

    static bool IsInstanceOf(Napi::Value value);
    static Napi::Value FromJson(const Napi::CallbackInfo& info);


private:
    static Napi::FunctionReference constructor;

    Napi::ObjectReference x;
    Napi::ObjectReference y;
    Napi::ObjectReference z;

    // Napi::Value ToString(const Napi::CallbackInfo& info);

    // Napi::Value ToJson(const Napi::CallbackInfo& info);

    void InitializeDistanceMembers(const Napi::Env& env);

    static Napi::Value IsA(const Napi::CallbackInfo& info);
};

#endif // _DISTANCE_VECTOR_
