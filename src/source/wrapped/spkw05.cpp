// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/spkw05.h"

extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"
#include "utility/unpack.h"
#include "utility/err.h"

Napi::Value spkw05(const Napi::CallbackInfo& info) {

    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceInt handle, body, center;
    std::string frame, segid;
    SpiceDouble first, last, gm;
    Napi::Array array;
    if(
      Unpack("spkw05", info)
      .i(handle, "handle")
      .i(body, "body")
      .i(center, "center")
      .str(frame, "frame")
      .d(first, "first")
      .d(last, "last")
      .str(segid, "segid")
      .d(gm, "gm")
      .getarray(array, "[{\"state\": {\"r\":[x,y,z], \"v\":[dx,dy,dz]}, \"et\": et}, ...]")
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        })){
        return env.Null();
    }

    struct StateContainer{
        SpiceDouble state[6];
    };

    SpiceInt n = array.Length();
    std::vector<SpiceDouble> epochs;
    std::vector<StateContainer> states;

    for(uint32_t i = 0; i < array.Length(); ++i){

        bool bIsElement = true;
        Napi::Value element = array.Get(i);
        bIsElement &= element.IsObject();
        if(bIsElement){
            Napi::Object elementObject = element.As<Napi::Object>();
            bIsElement &= elementObject.HasOwnProperty("state");
            bIsElement &= elementObject.HasOwnProperty("et");
            if(bIsElement){
                Napi::Value stateValue = elementObject.Get("state");
                Napi::Value etValue = elementObject.Get("et");
                bIsElement &= stateValue.IsObject();
                bIsElement &= etValue.IsNumber();
                if(bIsElement){
                    Napi::Object stateObject = stateValue.As<Napi::Object>();
                    bIsElement &= stateObject.HasOwnProperty("r");
                    bIsElement &= stateObject.HasOwnProperty("v");
                    if(bIsElement){
                        Napi::Value rValue = stateObject.Get("r");
                        Napi::Value vValue = stateObject.Get("v");
                        bIsElement &= rValue.IsArray();
                        bIsElement &= vValue.IsArray();
                        if(bIsElement){
                            Napi::Array rArray = rValue.As<Napi::Array>();
                            Napi::Array vArray = vValue.As<Napi::Array>();
                            bIsElement &= rArray.Length() == 3;
                            bIsElement &= vArray.Length() == 3;

                            if(bIsElement){
                                StateContainer state;
                                for(uint32_t j = 0; j < 3; ++j){
                                    Napi::Value rArrayElement = rArray.Get(j);
                                    Napi::Value vArrayElement = vArray.Get(j);
                                    bIsElement &= rArrayElement.IsNumber();
                                    bIsElement &= vArrayElement.IsNumber();
                                    if(bIsElement){
                                        state.state[0 + j] = rArrayElement.As<Napi::Number>().DoubleValue();
                                        state.state[3 + j] = vArrayElement.As<Napi::Number>().DoubleValue();
                                    }
                                }

                                states.push_back(state);
                                double et = etValue.As<Napi::Number>().DoubleValue();
                                epochs.push_back(et);
                            }
                        }
                    }
                }
            }
        }

        if(!bIsElement){
            Napi::TypeError::New(env, "invalid array element, array should be of form [{\"state\": {\"r\":[x, y, z], \"v\":[dx, dy, dz]}, \"et\":et}, ...]").ThrowAsJavaScriptException();
            return env.Null();                                
        }        
    }

    spkw05_c(handle, body, center, frame.c_str(), first, last, segid.c_str(), gm, n, &states[0], &epochs[0]);
  
    ErrorCheck(env);
    return env.Null(); 
}
