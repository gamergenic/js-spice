#include <napi.h>
#include "furnsh.h"
#include "unload.h"
#include "erract.h"
#include "errdev.h"
#include "errprt.h"
#include "str2et.h"
#include "spkpos.h"


Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set("str2et", Napi::Function::New(env, str2et));
  exports.Set("furnsh", Napi::Function::New(env, furnsh));
  exports.Set("unload", Napi::Function::New(env, unload));
  exports.Set("erract", Napi::Function::New(env, erract));
  exports.Set("errdev", Napi::Function::New(env, errdev));
  exports.Set("errprt", Napi::Function::New(env, errprt));
  exports.Set("str2et", Napi::Function::New(env, str2et));
  exports.Set("spkpos", Napi::Function::New(env, spkpos));
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)

#include "spice.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}

bool ErrorCheck(Napi::Env& env)
{
    SpiceBoolean failed = failed_c();

    if(failed)
    {
        char szBuffer[SpiceLongMessageMaxLength];

        szBuffer[0] = '\0';
        getmsg_c("LONG", sizeof(szBuffer), szBuffer);

        if (!strnlen(szBuffer, sizeof(szBuffer)))
        {
            szBuffer[0] = '\0';
            getmsg_c("SHORT", sizeof(szBuffer), szBuffer);
        }

        Napi::Error::New(env, szBuffer).ThrowAsJavaScriptException();
        return true;
    }

    return false;
}