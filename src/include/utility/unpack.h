// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#ifndef _UNPACK_
#define _UNPACK_

extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include <napi.h>
#include <string>

class Unpacker {

public:
    Unpacker(std::string _name, const Napi::CallbackInfo& _info);

    Unpacker& azl(SpiceDouble& range, SpiceDouble& az, SpiceDouble& el) { if(!isErred) { return _unpackdouble3("range", "az", "el", range, az, el); } return *this; }
    Unpacker& cyl(SpiceDouble& r, SpiceDouble& clon, SpiceDouble& z) { if(!isErred) { return _unpackdouble3("r", "clon", "z", r, clon, z); } return *this; }
    Unpacker& geo(SpiceDouble& lon, SpiceDouble& lat, SpiceDouble& alt) { if(!isErred) { return _unpackdouble3("lon", "lat", "alt", lon, lat, alt); } return *this; }
    Unpacker& lat(SpiceDouble& radius, SpiceDouble& lon, SpiceDouble& lat) { if(!isErred) { return _unpackdouble3("radius", "lon", "lat", radius, lon, lat); } return *this; }
    Unpacker& pgr(SpiceDouble& lon, SpiceDouble& lat, SpiceDouble& alt) { if(!isErred) { return _unpackdouble3("lon", "lat", "alt", lon, lat, alt); } return *this; }
    Unpacker& rad(SpiceDouble& range, SpiceDouble& ra, SpiceDouble& dec) { if(!isErred) { return _unpackdouble3("range", "ra", "dec", range, ra, dec); } return *this; }
    Unpacker& rec(SpiceDouble (&rec)[3], std::string name = "") { if(!isErred) { return _rec(rec, name); } return *this; }
    Unpacker& sph(SpiceDouble& r, SpiceDouble& colat, SpiceDouble& slon) { if(!isErred) { return _unpackdouble3("r", "colat", "slon", r, colat, slon); } return *this; }
    Unpacker& q(SpiceDouble (&q)[4], std::string name = "") { if(!isErred) { return _unpackquat(q, name); } return *this; }
    Unpacker& d(SpiceDouble& d, std::string name = "") { if(!isErred) { return _unpackdouble(d, name); } return *this; }
    Unpacker& et(SpiceDouble& et) { if(!isErred) { return _unpackdouble(et, "et"); } return *this; }
    Unpacker& dt(SpiceDouble& dt) { if(!isErred) { return _unpackdouble(dt, "dt"); } return *this; }
    Unpacker& angle(SpiceDouble& dt, std::string name = "rads") { if(!isErred) { return _unpackdouble(dt, name); } return *this; }
    Unpacker& flag(SpiceBoolean& _flag, std::string name="") { if(!isErred) { return _unpackbool(_flag, name);  } return *this; }
    Unpacker& str(std::string& _string, std::string name="") { if(!isErred) { return _unpackstring(_string, name); } return *this; }
    Unpacker& mat(SpiceDouble (&m)[3][3], std::string name="") { if(!isErred) { return _unpackdouble3x3(m, name); } return *this; }
    Unpacker& i(SpiceInt& i, std::string name = "") { if(!isErred) { return _unpackint(i, name); } return *this; }
    Unpacker& conics(SpiceDouble (&elts)[8]) { if(!isErred) { return _unpackconics(elts); } return *this; }
    Unpacker& geophs(SpiceDouble (&geophs)[8]) { if(!isErred) { return _unpackgeophs(geophs); } return *this; }
    Unpacker& tlelems(SpiceDouble (&tlelems)[10]) { if(!isErred) { return _unpackelems(tlelems); } return *this; }
    Unpacker& state(SpiceDouble (&state)[6], std::string name = "state") { if(!isErred) { return _unpackstate(state, name); } return *this; }
    Unpacker& getarray(Napi::Array& array, std::string name = "") { if(!isErred) { return _getarray(array, name); } return *this; }
    
    template<typename T>
    Unpacker& punt(T callback){
        if(!isErred) {
            int unpacked = callback(next(), *this);
            return advance(unpacked);
        }
        return *this;
    }

    template<typename T>
    bool check(T handleError){
        if(!isErred){
            if(remaining()){
                error("unexpected additional parameters");
            }
        }

        onError(handleError);
        return isErred;
    }

    template<typename T>
    Unpacker& onError(T handleError){
        if(isErred && !isErrHandled){
            handleError(name + ": " + errorMessage);
            isErrHandled = true;
        }
        return *this;
    }

    void setError(std::string err){
        error(err);
    }


    static Unpacker end;

private:
    Unpacker& _rec(SpiceDouble (&rec)[3], std::string name);
    Unpacker& _unpackdouble3(const char* name1, const char* name2, const char* name3, SpiceDouble& v1, SpiceDouble& v2, SpiceDouble& v3);
    Unpacker& _unpackdouble3x3(SpiceDouble (&m)[3][3], std::string name);
    Unpacker& _unpackdouble(SpiceDouble& value, std::string name);
    Unpacker& _unpackquat(SpiceDouble (&quat)[4], std::string name);
    Unpacker& _unpackbool(SpiceBoolean& value, std::string name);
    Unpacker& _unpackint(SpiceInt& value, std::string name);
    Unpacker& _unpackstring(std::string& value, std::string name);
    Unpacker& _unpackconics(SpiceDouble (&elts)[8]);
    Unpacker& _unpackgeophs(SpiceDouble (&elts)[8]);
    Unpacker& _unpackelems(SpiceDouble (&elems)[10]);
    template<int size>
    Unpacker& _unpackelts(SpiceDouble (&elts)[size], std::string (&members)[size], std::string name);
    Unpacker& _unpackstate(SpiceDouble (&state)[6], std::string name);
    Unpacker& _getarray(Napi::Array& array, std::string name);

    const Napi::CallbackInfo& info;
    const std::string name;

    uint32_t nextIndex { 0 };
    std::string errorMessage { std::string() };
    bool isErred { false };
    bool isErrHandled { false };

    int32_t remaining() { return info.Length() - nextIndex; }
    const Napi::Value next(int32_t plus = 0) { return info[nextIndex + plus]; }
    Unpacker& advance(int32_t plus = 1) { nextIndex += plus; return *this; }

    Unpacker& error(std::string message){
        if(!isErred){
            errorMessage = message;
            isErred = true;
        }
        return *this;
    }
};

Unpacker Unpack(std::string _name, const Napi::CallbackInfo& info);

#endif // _UNPACK_