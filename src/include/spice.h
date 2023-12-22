#ifndef _SPICE_
#define _SPICE_

#include <vector>

#include <napi.h>
bool ErrorCheck(Napi::Env& env);
bool ExtractRecVector(std::vector<Napi::Value> values, double result[3]);

constexpr int SpiceLongMessageMaxLength = 1841;

#endif // _SPICE_