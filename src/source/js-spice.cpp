#include <napi.h>
#include "wrapped/axisar.h"
#include "wrapped/azlrec.h"
#include "wrapped/b1900.h"
#include "wrapped/b1950.h"
#include "wrapped/bodvrd.h"
#include "wrapped/clight.h"
#include "wrapped/conics.h"
#include "wrapped/convrt.h"
#include "wrapped/cylrec.h"
#include "wrapped/deltet.h"
#include "wrapped/dpr.h"
#include "wrapped/erract.h"
#include "wrapped/errdev.h"
#include "wrapped/errprt.h"
#include "wrapped/et2utc.h"
#include "wrapped/etcal.h"
#include "wrapped/evsgp4.h"
#include "wrapped/furnsh.h"
#include "wrapped/georec.h"
#include "wrapped/getelm.h"
#include "wrapped/gfposc.h"
#include "wrapped/halfpi.h"
#include "wrapped/ident.h"
#include "wrapped/invert.h"
#include "wrapped/j1900.h"
#include "wrapped/j1950.h"
#include "wrapped/j2000.h"
#include "wrapped/j2100.h"
#include "wrapped/jyear.h"
#include "wrapped/latrec.h"
#include "wrapped/mxm.h"
#include "wrapped/mxv.h"
#include "wrapped/oscelt.h"
#include "wrapped/pgrrec.h"
#include "wrapped/pi.h"
#include "wrapped/rpd.h"
#include "wrapped/str2et.h"
#include "wrapped/spd.h"
#include "wrapped/sphrec.h"
#include "wrapped/spkpos.h"
#include "wrapped/timout.h"
#include "wrapped/radrec.h"
#include "wrapped/recazl.h"
#include "wrapped/reccyl.h"
#include "wrapped/recgeo.h"
#include "wrapped/reclat.h"
#include "wrapped/recpgr.h"
#include "wrapped/recrad.h"
#include "wrapped/recsph.h"
#include "wrapped/twopi.h"
#include "wrapped/unload.h"
#include "wrapped/vadd.h"
#include "wrapped/vcrss.h"
#include "wrapped/vdist.h"
#include "wrapped/vdot.h"
#include "wrapped/vhat.h"
#include "wrapped/vnorm.h"
#include "wrapped/xpose.h"

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set("axisar", Napi::Function::New(env, axisar));
  exports.Set("azlrec", Napi::Function::New(env, azlrec));
  exports.Set("b1900",  Napi::Function::New(env, b1900));
  exports.Set("b1950",  Napi::Function::New(env, b1950));
  exports.Set("bodvrd", Napi::Function::New(env, bodvrd));
  exports.Set("clight", Napi::Function::New(env, clight));
  exports.Set("conics", Napi::Function::New(env, conics));
  exports.Set("convrt", Napi::Function::New(env, convrt));
  exports.Set("cylrec", Napi::Function::New(env, cylrec));
  exports.Set("deltet", Napi::Function::New(env, deltet));
  exports.Set("dpr",    Napi::Function::New(env, dpr));
  exports.Set("erract", Napi::Function::New(env, erract));
  exports.Set("errdev", Napi::Function::New(env, errdev));
  exports.Set("errprt", Napi::Function::New(env, errprt));
  exports.Set("et2utc", Napi::Function::New(env, et2utc));
  exports.Set("etcal",  Napi::Function::New(env, etcal));
  exports.Set("evsgp4", Napi::Function::New(env, evsgp4));
  exports.Set("furnsh", Napi::Function::New(env, furnsh));
  exports.Set("georec", Napi::Function::New(env, georec));
  exports.Set("getelm", Napi::Function::New(env, getelm));
  exports.Set("gfposc", Napi::Function::New(env, gfposc));
  exports.Set("halfpi", Napi::Function::New(env, halfpi));
  exports.Set("ident",  Napi::Function::New(env, ident));
  exports.Set("invert", Napi::Function::New(env, invert));
  exports.Set("j1900",  Napi::Function::New(env, j1900));
  exports.Set("j1950",  Napi::Function::New(env, j1950));
  exports.Set("j2000",  Napi::Function::New(env, j2000));
  exports.Set("j2100",  Napi::Function::New(env, j2100));
  exports.Set("jyear",  Napi::Function::New(env, jyear));
  exports.Set("latrec", Napi::Function::New(env, latrec));
  exports.Set("mxm",    Napi::Function::New(env, mxm));
  exports.Set("mxv",    Napi::Function::New(env, mxv));
  exports.Set("oscelt", Napi::Function::New(env, oscelt));
  exports.Set("pgrrec", Napi::Function::New(env, pgrrec));
  exports.Set("pi",     Napi::Function::New(env, pi));
  exports.Set("radrec", Napi::Function::New(env, radrec));
  exports.Set("recazl", Napi::Function::New(env, recazl));
  exports.Set("reccyl", Napi::Function::New(env, reccyl));
  exports.Set("recgeo", Napi::Function::New(env, recgeo));
  exports.Set("reclat", Napi::Function::New(env, reclat));
  exports.Set("recpgr", Napi::Function::New(env, recpgr));
  exports.Set("recrad", Napi::Function::New(env, recrad));
  exports.Set("recsph", Napi::Function::New(env, recsph));
  exports.Set("rpd",    Napi::Function::New(env, rpd));
  exports.Set("str2et", Napi::Function::New(env, str2et));
  exports.Set("spd",    Napi::Function::New(env, spd));
  exports.Set("sphrec", Napi::Function::New(env, sphrec));
  exports.Set("spkpos", Napi::Function::New(env, spkpos));
  exports.Set("timout", Napi::Function::New(env, timout));
  exports.Set("twopi",  Napi::Function::New(env, twopi));
  exports.Set("unload", Napi::Function::New(env, unload));
  exports.Set("vadd",   Napi::Function::New(env, vadd));
  exports.Set("vcrss",  Napi::Function::New(env, vcrss));
  exports.Set("vdist",  Napi::Function::New(env, vdist));
  exports.Set("vdot",   Napi::Function::New(env, vdot));
  exports.Set("vhat",   Napi::Function::New(env, vhat));
  exports.Set("vnorm",  Napi::Function::New(env, vnorm));
  exports.Set("xpose",  Napi::Function::New(env, xpose));
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)