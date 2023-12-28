// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "wrapped/gfposc.h"
#include "utility/err.h"
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include <cmath>
#include <utility/pack.h>
#include <utility/unpack.h>

Napi::Value gfposc(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    std::string target, frame, abcorr, obsrvr, crdsys, coord, relate;
    SpiceDouble refval, adjust, step, totalWindow = 0;
    std::vector<std::pair<SpiceDouble, SpiceDouble>> cnfine_array;
    SpiceInt nintvls = 0;
    if(
      Unpack("spkpos", info)
      .str(target, "target")
      .str(frame, "frame")
      .str(abcorr, "abcorr")
      .str(obsrvr, "obsrvr")
      .str(crdsys, "crdsys")
      .str(coord, "coord")
      .str(relate, "relate")
      .d(refval, "refval")
      .d(adjust, "adjust")
      .d(step, "step")
      .windows(cnfine_array, totalWindow, "cnfine")
      .punt([&](Napi::Value Next, Unpacker& Unpacker){
        if(Next.IsNumber()){
            nintvls = Next.As<Napi::Number>().Int32Value();
            return 1;
        }

        Unpacker.setError("gfposc expected nintvls to be a numeric Int32 value");
        return 0;
      }, true)
      .check( [=](const std::string& error) {
            Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
        }, false)){
        return env.Null();
    }

  const int MAXWIN = 200;
  if (2 * cnfine_array.size() > MAXWIN)
  {
      setmsg_c("[cnfine] Window Segment count = #; maximum allowed value is #");
      errdp_c("#", cnfine_array.size());
      errdp_c("#", MAXWIN / 2);
      sigerr_c("SPICE(VALUEOUTOFRANGE)");
      ErrorCheck(env);
      return env.Null();
  }

  SPICEDOUBLE_CELL(_cnfine, MAXWIN);
  // Spice Cells are static.  They must reinitialized on every use or they
  // may have data sticking around.
  scard_c(0, &_cnfine);

  for(int i = 0; i < cnfine_array.size(); ++i){
    wninsd_c(cnfine_array[i].first, cnfine_array[i].second, &_cnfine);
  }

  if(!nintvls){
    int n = cnfine_array.size();
    double m = totalWindow;
    nintvls = (SpiceInt)std::ceil(2 * n + m / step);
  }


  // Outputs
  SPICEDOUBLE_CELL(_result, MAXWIN);
  scard_c(0, &_result);  

  SpiceCell*      cnfine = &_cnfine;
  SpiceCell*      result = &_result; 

  gfposc_c(
    target.c_str(),
    frame.c_str(),
    abcorr.c_str(),
    obsrvr.c_str(),
    crdsys.c_str(),
    coord.c_str(),
    relate.c_str(),
    refval,
    adjust,
    step,
    nintvls,
    cnfine,
    result
    );

  int resultsCount = wncard_c(result);
  std::vector<std::pair<double,double>> result_array;
  for (int i = 0; i < resultsCount; ++i)
  {
      double et1, et2;
      wnfetd_c(result, i, &et1, &et2);
      result_array.push_back(std::pair(et1, et2));
  }

  return Pack(info).windows(result_array).check();
}
