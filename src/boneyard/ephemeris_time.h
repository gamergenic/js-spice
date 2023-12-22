#ifndef _EPHEMERIS_TIME_
#define _EPHEMERIS_TIME_

#include <napi.h>

class EphemerisTime : public Napi::ObjectWrap<EphemerisTime> {
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    EphemerisTime(const Napi::CallbackInfo& info);

    static Napi::Object NewInstance(Napi::Env env, Napi::Value arg);
    static Napi::Value FromJson(const Napi::CallbackInfo& info);

    static Napi::Function GetConstructor(Napi::Env env) {
        return constructor.Value();
    }

    static Napi::Value FromEt(const Napi::CallbackInfo& info);
    static Napi::Value FromString(const Napi::CallbackInfo& info);
    
    static bool IsInstanceOf(Napi::Value value);
    static double ConvertValue(Napi::Value value);
    static bool CanConvert(Napi::Value value);
    static bool IsObject(Napi::Value value);

    static Napi::FunctionReference constructor;
private:
    double et;

    Napi::Value ToString(const Napi::CallbackInfo& info);

    Napi::Value ToJson(const Napi::CallbackInfo& info);

    static Napi::Value IsA(const Napi::CallbackInfo& info);
    Napi::Value GetEt(const Napi::CallbackInfo& info);
    Napi::Value GetString(const Napi::CallbackInfo& info);
    Napi::Value SetEt(const Napi::CallbackInfo& info);
    Napi::Value SetString(const Napi::CallbackInfo& info);

    Napi::Number ConvertTo(const Napi::CallbackInfo& info, const char* out);    
    static Napi::Value ConvertFrom(const Napi::CallbackInfo& info, const char* out);

    static bool Add(Napi::Value& out, const EphemerisTime& lhs, const Napi::Value& rhs);
    static bool Subtract(Napi::Value& out, const EphemerisTime& lhs, const Napi::Value& rhs);

    Napi::Value Add(const Napi::CallbackInfo& info);
    Napi::Value Subtract(const Napi::CallbackInfo& info);
};

#endif // _EPHEMERIS_TIME_