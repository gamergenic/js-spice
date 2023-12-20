#ifndef _SPICE_
#define _SPICE_

#include <napi.h>
bool ErrorCheck(Napi::Env& env);

constexpr int SpiceLongMessageMaxLength = 1841;

#endif // _SPICE_