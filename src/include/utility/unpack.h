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
    Unpacker& rec(SpiceDouble (&rec)[3]) { if(!isErred) { return _rec(rec); } return *this; }
    Unpacker& sph(SpiceDouble& r, SpiceDouble& colat, SpiceDouble& slon) { if(!isErred) { return _unpackdouble3("r", "colat", "slon", r, colat, slon); } return *this; }
    Unpacker& d(SpiceDouble& d, std::string name = "") { if(!isErred) { return _unpackdouble(d, name); } return *this; }
    Unpacker& et(SpiceDouble& et) { if(!isErred) { return _unpackdouble(et, "et"); } return *this; }
    Unpacker& dt(SpiceDouble& dt) { if(!isErred) { return _unpackdouble(dt, "dt"); } return *this; }
    Unpacker& angle(SpiceDouble& dt, std::string name = "rads") { if(!isErred) { return _unpackdouble(dt, name); } return *this; }
    Unpacker& flag(SpiceBoolean& _flag, std::string name="") { if(!isErred) { return _unpackbool(_flag, name);  } return *this; }
    Unpacker& str(std::string& _string, std::string name="") { if(!isErred) { return _unpackstring(_string, name); } return *this; }
    Unpacker& mat(SpiceDouble (&m)[3][3], std::string name="") { if(!isErred) { return _unpackdouble3x3(m, name); } return *this; }

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

    static Unpacker end;

private:
    Unpacker& _rec(SpiceDouble (&rec)[3]);
    Unpacker& _unpackdouble3(const char* name1, const char* name2, const char* name3, SpiceDouble& v1, SpiceDouble& v2, SpiceDouble& v3);
    Unpacker& _unpackdouble3x3(SpiceDouble (&m)[3][3], std::string name);
    Unpacker& _unpackdouble(SpiceDouble& value, std::string name);
    Unpacker& _unpackbool(SpiceBoolean& value, std::string name);
    Unpacker& _unpackstring(std::string& value, std::string name);

    const Napi::CallbackInfo& info;
    const std::string name;

    uint32_t nextIndex { 0 };
    std::string errorMessage { std::string() };
    bool isErred { false };
    bool isErrHandled { false };

    int32_t remaining() { return info.Length() - nextIndex; }
    const Napi::Value& next(int32_t plus = 0) { return info[nextIndex + plus]; }
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