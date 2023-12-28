// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#ifndef _ERR_
#define _ERR_

// Small curiosity - 
// Q: why is this file not called "error.h"?
// A: filenames "error"-anything cause false positives when searching build logs for an error.

#include <napi.h>
bool ErrorCheck(Napi::Env env);
#endif // _ERR_