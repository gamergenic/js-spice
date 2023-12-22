#ifndef _EPHEMERIS_PERIOD_
#define _EPHEMERIS_PERIOD_

#include <napi.h>

class EphemerisPeriod : public Napi::ObjectWrap<EphemerisPeriod> {
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    EphemerisPeriod(const Napi::CallbackInfo& info);

    static Napi::Object NewInstance(Napi::Env env, Napi::Value arg);
    static Napi::Value FromJson(const Napi::CallbackInfo& info);

    static Napi::Function GetConstructor(Napi::Env env) {
        return constructor.Value();
    }

    static Napi::Value FromSeconds(const Napi::CallbackInfo& info);
    static Napi::Value FromMinutes(const Napi::CallbackInfo& info);
    static Napi::Value FromHours(const Napi::CallbackInfo& info);
    static Napi::Value FromDays(const Napi::CallbackInfo& info);
    static Napi::Value FromJulianYears(const Napi::CallbackInfo& info);
    static Napi::Value FromTropicalYears(const Napi::CallbackInfo& info);
    
    static bool IsInstanceOf(Napi::Value value);
    static double ConvertValue(Napi::Value value);
    static bool CanConvert(Napi::Value value);
    static bool IsObject(Napi::Value value);

    static Napi::FunctionReference constructor;
private:
    double dt;

    Napi::Value ToString(const Napi::CallbackInfo& info);

    Napi::Value ToJson(const Napi::CallbackInfo& info);

    static Napi::Value IsA(const Napi::CallbackInfo& info);

    Napi::Value GetSeconds(const Napi::CallbackInfo& info);
    Napi::Value GetMinutes(const Napi::CallbackInfo& info);
    Napi::Value GetHours(const Napi::CallbackInfo& info);
    Napi::Value GetDays(const Napi::CallbackInfo& info);
    Napi::Value GetJulianYears(const Napi::CallbackInfo& info);
    Napi::Value GetTropicalYears(const Napi::CallbackInfo& info);

    Napi::Value SetSeconds(const Napi::CallbackInfo& info);
    Napi::Value SetMinutes(const Napi::CallbackInfo& info);
    Napi::Value SetHours(const Napi::CallbackInfo& info);
    Napi::Value SetDays(const Napi::CallbackInfo& info);
    Napi::Value SetJulianYears(const Napi::CallbackInfo& info);
    Napi::Value SetTropicalYears(const Napi::CallbackInfo& info);

    Napi::Value SetFrom(const Napi::CallbackInfo& info, const char* out);    
    Napi::Number ConvertTo(const Napi::CallbackInfo& info, const char* out);    
    static Napi::Value ConvertFrom(const Napi::CallbackInfo& info, const char* out);    

    Napi::Value Add(const Napi::CallbackInfo& info);
    Napi::Value Subtract(const Napi::CallbackInfo& info);
    Napi::Value Multiply(const Napi::CallbackInfo& info);
    Napi::Value Divide(const Napi::CallbackInfo& info);
    Napi::Value Mod(const Napi::CallbackInfo& info);

    static bool Add(Napi::Value& out, const EphemerisPeriod& lhs, const Napi::Value& rhs);
    static bool Subtract(Napi::Value& out, const EphemerisPeriod& lhs, const Napi::Value& rhs);
    static bool Multiply(Napi::Value& out, const EphemerisPeriod& lhs, const Napi::Value& rhs);
    static bool Divide(Napi::Value& out, const EphemerisPeriod& lhs, const Napi::Value& rhs);
    static bool Mod(Napi::Value& out, const EphemerisPeriod& lhs, const Napi::Value& rhs);
};

#endif // _EPHEMERIS_PERIOD_