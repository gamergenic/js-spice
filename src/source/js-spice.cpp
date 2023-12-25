#include <napi.h>
#include "wrapped/axisar.h"
#include "wrapped/azlrec.h"
#include "wrapped/bodvrd.h"
#include "wrapped/convrt.h"
#include "wrapped/cylrec.h"
#include "wrapped/dpr.h"
#include "wrapped/erract.h"
#include "wrapped/errdev.h"
#include "wrapped/errprt.h"
#include "wrapped/furnsh.h"
#include "wrapped/georec.h"
#include "wrapped/gfposc.h"
#include "wrapped/halfpi.h"
#include "wrapped/ident.h"
#include "wrapped/latrec.h"
#include "wrapped/mxm.h"
#include "wrapped/mxv.h"
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
  exports.Set("bodvrd", Napi::Function::New(env, bodvrd));
  exports.Set("convrt", Napi::Function::New(env, convrt));
  exports.Set("cylrec", Napi::Function::New(env, cylrec));
  exports.Set("dpr",    Napi::Function::New(env, dpr));
  exports.Set("erract", Napi::Function::New(env, erract));
  exports.Set("errdev", Napi::Function::New(env, errdev));
  exports.Set("errprt", Napi::Function::New(env, errprt));
  exports.Set("furnsh", Napi::Function::New(env, furnsh));
  exports.Set("georec", Napi::Function::New(env, georec));
  exports.Set("gfposc", Napi::Function::New(env, gfposc));
  exports.Set("halfpi", Napi::Function::New(env, halfpi));
  exports.Set("ident",  Napi::Function::New(env, ident));
  exports.Set("latrec", Napi::Function::New(env, latrec));
  exports.Set("mxm",    Napi::Function::New(env, mxm));
  exports.Set("mxv",    Napi::Function::New(env, mxv));
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