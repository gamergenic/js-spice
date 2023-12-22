#ifndef _DISTANCE_
#define _DISTANCE_

#include <napi.h>

class Distance : public Napi::ObjectWrap<Distance> {
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    Distance(const Napi::CallbackInfo& info);
    ~Distance();

    static Napi::Object NewInstance(Napi::Env env, Napi::Value arg);
    static Napi::Value FromJson(const Napi::CallbackInfo& info);

    static Napi::Value FromMeters(const Napi::CallbackInfo& info);
    static Napi::Value FromKilometers(const Napi::CallbackInfo& info);
    static Napi::Value FromCentimeters(const Napi::CallbackInfo& info);
    static Napi::Value FromMillimeters(const Napi::CallbackInfo& info);
    static Napi::Value FromFeet(const Napi::CallbackInfo& info);
    static Napi::Value FromInches(const Napi::CallbackInfo& info);
    static Napi::Value FromYards(const Napi::CallbackInfo& info);
    static Napi::Value FromStatuteMiles(const Napi::CallbackInfo& info);
    static Napi::Value FromNauticalMiles(const Napi::CallbackInfo& info);
    static Napi::Value FromAstronomicalUnits(const Napi::CallbackInfo& info);
    static Napi::Value FromParsecs(const Napi::CallbackInfo& info);
    static Napi::Value FromLightSeconds(const Napi::CallbackInfo& info);
    static Napi::Value FromLightYears(const Napi::CallbackInfo& info);

    static Napi::Function GetConstructor(Napi::Env env) {
        return constructor.Value();
    }

    static bool IsInstanceOf(Napi::Value value);
    static double ConvertValue(Napi::Value value);
    static bool CanConvert(Napi::Value value);
    static bool IsObject(Napi::Value value);

    static Napi::FunctionReference constructor;
private:
    double km;

    Napi::Value ToString(const Napi::CallbackInfo& info);

    Napi::Value ToJson(const Napi::CallbackInfo& info);

    static Napi::Value IsA(const Napi::CallbackInfo& info);
    Napi::Value GetKilometers(const Napi::CallbackInfo& info);
    Napi::Value GetMeters(const Napi::CallbackInfo& info);
    Napi::Value GetCentimeters(const Napi::CallbackInfo& info);
    Napi::Value GetMillimeters(const Napi::CallbackInfo& info);
    Napi::Value GetFeet(const Napi::CallbackInfo& info);
    Napi::Value GetInches(const Napi::CallbackInfo& info);
    Napi::Value GetYards(const Napi::CallbackInfo& info);
    Napi::Value GetStatuteMiles(const Napi::CallbackInfo& info);
    Napi::Value GetNauticalMiles(const Napi::CallbackInfo& info);
    Napi::Value GetAstronomicalUnits(const Napi::CallbackInfo& info);
    Napi::Value GetParsecs(const Napi::CallbackInfo& info);
    Napi::Value GetLightSeconds(const Napi::CallbackInfo& info);
    Napi::Value GetLightYears(const Napi::CallbackInfo& info);
    Napi::Value SetKilometers(const Napi::CallbackInfo& info);
    Napi::Value SetMeters(const Napi::CallbackInfo& info);
    Napi::Value SetCentimeters(const Napi::CallbackInfo& info);
    Napi::Value SetMillimeters(const Napi::CallbackInfo& info);
    Napi::Value SetFeet(const Napi::CallbackInfo& info);
    Napi::Value SetInches(const Napi::CallbackInfo& info);
    Napi::Value SetYards(const Napi::CallbackInfo& info);
    Napi::Value SetStatuteMiles(const Napi::CallbackInfo& info);
    Napi::Value SetNauticalMiles(const Napi::CallbackInfo& info);
    Napi::Value SetAstronomicalUnits(const Napi::CallbackInfo& info);
    Napi::Value SetParsecs(const Napi::CallbackInfo& info);
    Napi::Value SetLightSeconds(const Napi::CallbackInfo& info);
    Napi::Value SetLightYears(const Napi::CallbackInfo& info);
    Napi::Value SetFrom(const Napi::CallbackInfo& info, const char* inUnits);    

    Napi::Number ConvertTo(const Napi::CallbackInfo& info, const char* out);    
    static Napi::Value ConvertFrom(const Napi::CallbackInfo& info, const char* out);

    static bool Add(Napi::Value& out, const Distance& lhs, const Napi::Value& rhs);
    static bool Subtract(Napi::Value& out, const Distance& lhs, const Napi::Value& rhs);
    static bool Multiply(Napi::Value& out, const Distance& lhs, const Napi::Value& rhs);
    static bool Divide(Napi::Value& out, const Distance& lhs, const Napi::Value& rhs);
    static bool Mod(Napi::Value& out, const Distance& lhs, const Napi::Value& rhs);

    Napi::Value Add(const Napi::CallbackInfo& info);
    Napi::Value Subtract(const Napi::CallbackInfo& info);
    Napi::Value Multiply(const Napi::CallbackInfo& info);
    Napi::Value Divide(const Napi::CallbackInfo& info);
    Napi::Value Mod(const Napi::CallbackInfo& info);
};

#endif // _DISTANCE_