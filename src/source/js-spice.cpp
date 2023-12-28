// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

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
#include "wrapped/eul2m.h"
#include "wrapped/evsgp4.h"
#include "wrapped/furnsh.h"
#include "wrapped/georec.h"
#include "wrapped/getelm.h"
#include "wrapped/gfposc.h"
#include "wrapped/gfsep.h"
#include "wrapped/halfpi.h"
#include "wrapped/ident.h"
#include "wrapped/invert.h"
#include "wrapped/j1900.h"
#include "wrapped/j1950.h"
#include "wrapped/j2000.h"
#include "wrapped/j2100.h"
#include "wrapped/jyear.h"
#include "wrapped/latrec.h"
#include "wrapped/m2q.h"
#include "wrapped/m2eul.h"
#include "wrapped/mtxm.h"
#include "wrapped/mtxv.h"
#include "wrapped/mxm.h"
#include "wrapped/mxmt.h"
#include "wrapped/mxv.h"
#include "wrapped/oscelt.h"
#include "wrapped/pckfrm.h"
#include "wrapped/pgrrec.h"
#include "wrapped/pi.h"
#include "wrapped/prop2b.h"
#include "wrapped/pxform.h"
#include "wrapped/pxfrm2.h"
#include "wrapped/q2m.h"
#include "wrapped/qxq.h"
#include "wrapped/rotate.h"
#include "wrapped/rpd.h"
#include "wrapped/str2et.h"
#include "wrapped/spd.h"
#include "wrapped/sphrec.h"
#include "wrapped/spkcls.h"
#include "wrapped/spkcpo.h"
#include "wrapped/spkcpt.h"
#include "wrapped/spkcvo.h"
#include "wrapped/spkcvt.h"
#include "wrapped/spkezr.h"
#include "wrapped/spkgeo.h"
#include "wrapped/spkgps.h"
#include "wrapped/spkobj.h"
#include "wrapped/spkopn.h"
#include "wrapped/spkpos.h"
#include "wrapped/spkw05.h"
#include "wrapped/sxform.h"
#include "wrapped/timout.h"
#include "wrapped/radrec.h"
#include "wrapped/raxisa.h"
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
#include "wrapped/vequ.h"
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
  exports.Set("eul2m",  Napi::Function::New(env, eul2m));
  exports.Set("evsgp4", Napi::Function::New(env, evsgp4));
  exports.Set("furnsh", Napi::Function::New(env, furnsh));
  exports.Set("georec", Napi::Function::New(env, georec));
  exports.Set("getelm", Napi::Function::New(env, getelm));
  exports.Set("gfposc", Napi::Function::New(env, gfposc));
  exports.Set("gfsep",  Napi::Function::New(env, gfsep));
  exports.Set("halfpi", Napi::Function::New(env, halfpi));
  exports.Set("ident",  Napi::Function::New(env, ident));
  exports.Set("invert", Napi::Function::New(env, invert));
  exports.Set("j1900",  Napi::Function::New(env, j1900));
  exports.Set("j1950",  Napi::Function::New(env, j1950));
  exports.Set("j2000",  Napi::Function::New(env, j2000));
  exports.Set("j2100",  Napi::Function::New(env, j2100));
  exports.Set("jyear",  Napi::Function::New(env, jyear));
  exports.Set("latrec", Napi::Function::New(env, latrec));
  exports.Set("m2eul",  Napi::Function::New(env, m2eul));
  exports.Set("m2q",    Napi::Function::New(env, m2q));
  exports.Set("mtxm",   Napi::Function::New(env, mtxm));
  exports.Set("mtxv",   Napi::Function::New(env, mtxv));
  exports.Set("mxm",    Napi::Function::New(env, mxm));
  exports.Set("mxmt",   Napi::Function::New(env, mxmt));
  exports.Set("mxv",    Napi::Function::New(env, mxv));
  exports.Set("oscelt", Napi::Function::New(env, oscelt));
  exports.Set("pckfrm", Napi::Function::New(env, pckfrm));
  exports.Set("pgrrec", Napi::Function::New(env, pgrrec));
  exports.Set("pi",     Napi::Function::New(env, pi));
  exports.Set("prop2b", Napi::Function::New(env, prop2b));
  exports.Set("pxform", Napi::Function::New(env, pxform));
  exports.Set("pxfrm2", Napi::Function::New(env, pxfrm2));
  exports.Set("q2m",    Napi::Function::New(env, q2m));
  exports.Set("qxq",    Napi::Function::New(env, qxq));
  exports.Set("radrec", Napi::Function::New(env, radrec));
  exports.Set("raxisa", Napi::Function::New(env, raxisa));
  exports.Set("recazl", Napi::Function::New(env, recazl));
  exports.Set("reccyl", Napi::Function::New(env, reccyl));
  exports.Set("recgeo", Napi::Function::New(env, recgeo));
  exports.Set("reclat", Napi::Function::New(env, reclat));
  exports.Set("recpgr", Napi::Function::New(env, recpgr));
  exports.Set("recrad", Napi::Function::New(env, recrad));
  exports.Set("recsph", Napi::Function::New(env, recsph));
  exports.Set("rotate", Napi::Function::New(env, rotate));
  exports.Set("rpd",    Napi::Function::New(env, rpd));
  exports.Set("str2et", Napi::Function::New(env, str2et));
  exports.Set("spd",    Napi::Function::New(env, spd));
  exports.Set("sphrec", Napi::Function::New(env, sphrec));
  exports.Set("spkcls", Napi::Function::New(env, spkcls));
  exports.Set("spkcpo", Napi::Function::New(env, spkcpo));
  exports.Set("spkcpt", Napi::Function::New(env, spkcpt));
  exports.Set("spkcvo", Napi::Function::New(env, spkcvo));
  exports.Set("spkcvt", Napi::Function::New(env, spkcvt));
  exports.Set("spkezr", Napi::Function::New(env, spkezr));
  exports.Set("spkgeo", Napi::Function::New(env, spkgeo));
  exports.Set("spkgps", Napi::Function::New(env, spkgps));
  exports.Set("spkobj", Napi::Function::New(env, spkobj));
  exports.Set("spkopn", Napi::Function::New(env, spkopn));
  exports.Set("spkpos", Napi::Function::New(env, spkpos));
  exports.Set("spkw05", Napi::Function::New(env, spkw05));
  exports.Set("sxform", Napi::Function::New(env, sxform));
  exports.Set("timout", Napi::Function::New(env, timout));
  exports.Set("twopi",  Napi::Function::New(env, twopi));
  exports.Set("unload", Napi::Function::New(env, unload));
  exports.Set("vadd",   Napi::Function::New(env, vadd));
  exports.Set("vcrss",  Napi::Function::New(env, vcrss));
  exports.Set("vdist",  Napi::Function::New(env, vdist));
  exports.Set("vdot",   Napi::Function::New(env, vdot));
  exports.Set("vequ",   Napi::Function::New(env, vequ));
  exports.Set("vhat",   Napi::Function::New(env, vhat));
  exports.Set("vnorm",  Napi::Function::New(env, vnorm));
  exports.Set("xpose",  Napi::Function::New(env, xpose));
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)