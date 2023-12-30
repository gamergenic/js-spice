// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "utility/err.h"
#include "js-spice.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}

bool ErrorCheck(Napi::Env env)
{
    SpiceBoolean failed = failed_c();

    if(failed)
    {
        char szBuffer[SpiceLongMessageMaxLength];

        szBuffer[0] = '\0';
        getmsg_c("DEFAULT", sizeof(szBuffer), szBuffer);

        if (!strnlen(szBuffer, sizeof(szBuffer)))
        {
            getmsg_c("LONG", sizeof(szBuffer), szBuffer);
            if (!strnlen(szBuffer, sizeof(szBuffer)))
            {
                getmsg_c("SHORT", sizeof(szBuffer), szBuffer);
            }
        }

        reset_c();

        Napi::Error::New(env, szBuffer).ThrowAsJavaScriptException();
        return true;
    }

    return false;
}
