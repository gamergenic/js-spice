#include "utility/err.h"
#include "js-spice.h"
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
