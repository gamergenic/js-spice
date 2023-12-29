// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/furnsh.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include <vector>
#include <string>
using std::vector;
using std::string;

Napi::Value furnsh(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    vector<string> paths;

    // Look for a string or array of strings for each arg...
    for(uint32_t i = 0; i < info.Length(); ++i){
        if (!info[i].IsString() && !info[i].IsArray()) {
            Napi::TypeError::New(env, "furnsh expected a string file path or array of string paths").ThrowAsJavaScriptException();
            return env.Null();
        }
        if(info[i].IsString()){
            paths.push_back(info[i].As<Napi::String>().Utf8Value());
            continue;
        }
        Napi::Array array = info[i].As<Napi::Array>();
        for(uint32_t j = 0; j < array.Length(); ++j){
            if (!array.Get(j).IsString()){
                Napi::TypeError::New(env, "furnsh expected an array of string paths, but found a non-string").ThrowAsJavaScriptException();
                return env.Null();
            }
            paths.push_back(array.Get(j).As<Napi::String>().Utf8Value());
        }
    }

    for(vector<string>::iterator it = paths.begin(); it != paths.end(); ++it){
        furnsh_c((*it).c_str());
        if(ErrorCheck(env)){
            break;
        }
    }

    return env.Null();
}
