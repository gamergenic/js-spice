#include "spkpos.h"
#include "spice.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include "ephemeris_time.h"
#include <iostream>
#include <string>

Napi::Value spkpos(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    Napi::HandleScope scope(env);

    if(info.Length() != 5){
        Napi::TypeError::New(env, "spkpos expected 5 parameters (targ, et, ref, abcorr, obs)").ThrowAsJavaScriptException();    
        return env.Null();
    }

    double et;

    std::string targ_str;
    std::string ref_str;
    std::string abcorr_str;
    std::string obs_str;

    if(info[0].IsString()){
        targ_str = info[0].ToString().Utf8Value();            
    }
    else {
        Napi::TypeError::New(env, "spkpos(targ, et, ref, abcorr, obs) expected targ as string").ThrowAsJavaScriptException();    
        return env.Null();
    }

    if(EphemerisTime::CanConvert(info[1])){
        et = EphemerisTime::ConvertValue(info[1]);            
    }
    else {
        Napi::TypeError::New(env, "spkpos(targ, et, ref, abcorr, obs) expected et as ephemeris time, { et: }, or number representing seconds since J2000").ThrowAsJavaScriptException();    
        return env.Null();
    }

    if(info[2].IsString()){
        ref_str = info[2].ToString().Utf8Value();            
    }
    else {
        Napi::TypeError::New(env, "spkpos(targ, et, ref, abcorr, obs) expected ref as string").ThrowAsJavaScriptException();    
        return env.Null();
    }

    if(info[3].IsString()){
        abcorr_str = info[3].ToString().Utf8Value();            
    }
    else {
        Napi::TypeError::New(env, "spkpos(targ, et, ref, abcorr, obs) expected abcorr as string").ThrowAsJavaScriptException();    
        return env.Null();
    }

    if(info[4].IsString()){
        obs_str = info[4].ToString().Utf8Value();            
    }
    else {
        Napi::TypeError::New(env, "spkpos(targ, et, ref, abcorr, obs) expected obs as string").ThrowAsJavaScriptException();    
        return env.Null();
    }

    ConstSpiceChar* targ = targ_str.c_str(); 
    ConstSpiceChar* ref = ref_str.c_str(); 
    ConstSpiceChar* abcorr = abcorr_str.c_str();
    ConstSpiceChar* obs = obs_str.c_str();
    SpiceDouble     ptarg[3];
    SpiceDouble     lt;

    spkpos_c(targ, et, ref, abcorr, obs, ptarg, &lt);

    Napi::Object obj = Napi::Object::New(env);

    obj.Set("x", ptarg[0]);
    obj.Set("y", ptarg[1]);
    obj.Set("z", ptarg[2]);    
    obj.Set("lt", lt);    

    return obj;
}
