#ifndef _PACK_
#define _PACK_

#include <napi.h>
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/err.h"

template <typename T>
class NValue : public T {

public:    

    Napi::Value check(){
        if(ErrorCheck(value.Env())){
            return value.Env().Null();
        }

        return value;
    }

    Napi::Value nocheck(){
        return value;
    }


protected:
    T value;
};


class NObject : public NValue<Napi::Object> {

public:    
    NObject(Napi::Env& env) {
        value = Napi::Object::New(env);
    }

    Napi::Object obj() { return value; }
};

class NDouble : public NValue<Napi::Number> {

public:    
    NDouble(Napi::Env& env, SpiceDouble _value) {
        value = Napi::Number::New(env, _value);
    }
};

class NInt : public NValue<Napi::Number> {

public:    
    NInt(Napi::Env& env, SpiceInt _value) {
        value = Napi::Number::New(env, _value);
    }
};


class NFlag : public NValue<Napi::Boolean> {

public:    
    NFlag(Napi::Env& env, bool _value) {
        value = Napi::Boolean::New(env, _value);
    }
};

class NArrayDouble3 : public NValue<Napi::Array> {
public:    
    NArrayDouble3(Napi::Env& env, const double (&_value)[3]) {
        value = Napi::Array::New(env, 3);
        value.Set((uint32_t)0, _value[0]);
        value.Set((uint32_t)1, _value[1]);
        value.Set((uint32_t)2, _value[2]);
    }

    Napi::Array array() { return value; }
};

class NArrayDouble3x3 : public NValue<Napi::Array> {
public:    
    NArrayDouble3x3(Napi::Env& env, const double (&_value)[3][3]) {
        const uint32_t m = 3, n = 3;
        value = Napi::Array::New(env, m);
        for(uint32_t i = 0; i < m; ++i){
            Napi::Array row = Napi::Array::New(env, n);
            for(uint32_t j = 0; j < n; ++j){
                row.Set(j, _value[i][j]);
            }
            value.Set(i, row);
        }
    }

    Napi::Array array() { return value; }
};


class NString : public NValue<Napi::String> {

public:    
    NString(Napi::Env& env, ConstSpiceChar* _value) {
        value = Napi::String::New(env, _value);
    }
};


class Packer{

public:
    Packer(Napi::Env _env);

    NObject azl(SpiceDouble range, SpiceDouble az, SpiceDouble el);
    NObject cyl(SpiceDouble r, SpiceDouble clon, SpiceDouble z);
    NObject geo(SpiceDouble lon, SpiceDouble lat, SpiceDouble alt);
    NObject lat(SpiceDouble radius, SpiceDouble lon, SpiceDouble lat);
    NObject pgr(SpiceDouble lon, SpiceDouble lat, SpiceDouble alt);
    NObject rad(SpiceDouble range, SpiceDouble ra, SpiceDouble dec);
    NArrayDouble3  rec(ConstSpiceDouble (&rectan)[3]);
    NObject sph(SpiceDouble r, SpiceDouble colat, SpiceDouble slon);
    NDouble et(SpiceDouble et);
    NDouble dt(SpiceDouble dt);
    NDouble d(SpiceDouble d);
    NDouble dist(SpiceDouble dist);
    NInt i(SpiceInt i);
    NFlag flag(SpiceBoolean flag);
    NArrayDouble3x3 mat(SpiceDouble (&m)[3][3]);
    NString str(ConstSpiceChar* str);
private:
    Napi::Env env;
};

Packer Pack(const Napi::CallbackInfo& _info);
Packer Pack(Napi::Env _env);

#endif // _PACK_