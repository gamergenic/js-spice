// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#ifndef _PACK_
#define _PACK_

#include <napi.h>
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "utility/err.h"

class NObject;

template <typename T>
class NValue : public T {

public:    

    Napi::Value check(){
        if(ErrorCheck(value.Env())){
            return value.Env().Null();
        }

        return value;
    }

    NObject as(std::string recName);

    Napi::Value nocheck(){
        return value;
    }

protected:
    T value;
};


class NObject : public NValue<Napi::Object> {

public:    
    NObject(Napi::Env env) {
        value = Napi::Object::New(env);
    }

    NObject& with(SpiceDouble value, std::string name){
        obj().Set(name, Napi::Number::New(obj().Env(), value));
        return *this;
    }

    Napi::Object obj() { return value; }
};

template <typename T>
NObject NValue<T>::as(std::string recName){
    NObject result = NObject(value.Env());
    result.obj().Set(recName, value);
    return result;
}

class NDouble : public NValue<Napi::Number> {

public:    
    NDouble(Napi::Env env, SpiceDouble _value) {
        value = Napi::Number::New(env, _value);
    }
};

class NInt : public NValue<Napi::Number> {

public:    
    NInt(Napi::Env env, SpiceInt _value) {
        value = Napi::Number::New(env, _value);
    }
};


class NFlag : public NValue<Napi::Boolean> {

public:    
    NFlag(Napi::Env env, bool _value) {
        value = Napi::Boolean::New(env, _value);
    }
};

class NArrayDouble3 : public NValue<Napi::Array> {
public:    
    NArrayDouble3(Napi::Env env, const double (&_value)[3]) {
        value = Napi::Array::New(env, 3);
        value.Set((uint32_t)0, _value[0]);
        value.Set((uint32_t)1, _value[1]);
        value.Set((uint32_t)2, _value[2]);
    }

    Napi::Array array() { return value; }
};

template<uint32_t m, uint32_t n>
class NArrayDoubleMxN : public NValue<Napi::Array> {
public:    
    NArrayDoubleMxN(Napi::Env env, const double (&_value)[m][n]) {
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


typedef NArrayDoubleMxN<3,3> NArrayDouble3x3;
typedef NArrayDoubleMxN<6,6> NArrayDouble6x6;


class NString : public NValue<Napi::String> {

public:    
    NString(Napi::Env env, ConstSpiceChar* _value) {
        value = Napi::String::New(env, _value);
    }
};


class NState : public NValue<Napi::Object> {
public:    
    NState(Napi::Env env, ConstSpiceDouble (&_value)[6]) {
        value = Napi::Object::New(env);

        Napi::Array r = Napi::Array::New(env, 3);
        Napi::Array v = Napi::Array::New(env, 3);
        for(uint32_t i = 0; i < 3; ++i){
            r.Set(i, _value[i]);
            v.Set(i, _value[3 + i]);
        }
        value.Set("r", r);
        value.Set("v", v);
    }

    Napi::Object object() { return value; }
};

class NElts : public NValue<Napi::Object> {
public:

    template<int size>
    NElts(Napi::Env env, const std::string (&members)[size], ConstSpiceDouble (&_value)[size]) {
        value = Napi::Object::New(env);

        for(uint32_t i = 0; i < size; ++i){
            value.Set(members[i], _value[i]);
        }
    }

    Napi::Object object() { return value; }
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
    NObject q(ConstSpiceDouble (&q)[4]);
    NDouble et(SpiceDouble et);
    NDouble dt(SpiceDouble dt);
    NDouble d(SpiceDouble d);
    NDouble dist(SpiceDouble dist);
    NState state(ConstSpiceDouble (&state)[6]);
    NInt i(SpiceInt i);
    NFlag flag(SpiceBoolean flag);
    NArrayDouble3x3 mat(SpiceDouble (&m)[3][3]);
    NArrayDouble6x6 statemat(SpiceDouble (&m)[6][6]);
    NString str(ConstSpiceChar* str);
    NElts conics(ConstSpiceDouble (&elts)[8]);
    NElts elms(ConstSpiceDouble (&elms)[10]);
    NElts geophs(ConstSpiceDouble (&elms)[8]);
private:
    Napi::Env env;
};

Packer Pack(const Napi::CallbackInfo& _info);
Packer Pack(Napi::Env _env);

#endif // _PACK_