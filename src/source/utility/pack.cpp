// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "utility/pack.h"

Packer::Packer(Napi::Env _env) : env(_env) {
}


NObject Packer::azl(SpiceDouble range, SpiceDouble az, SpiceDouble el){
    NObject result(env);

    result.obj().Set("range", range);
    result.obj().Set("az", az);
    result.obj().Set("el", el);

    return result;
}

NObject Packer::cyl(SpiceDouble r, SpiceDouble clon, SpiceDouble z){
    NObject result(env);

    result.obj().Set("r", r);
    result.obj().Set("clon", clon);
    result.obj().Set("z", z);

    return result;
}

NObject Packer::geo(SpiceDouble lon, SpiceDouble lat, SpiceDouble alt){
    NObject result(env);

    result.obj().Set("lon", lon);
    result.obj().Set("lat", lat);
    result.obj().Set("alt", alt);

    return result;
}

NObject Packer::lat(SpiceDouble radius, SpiceDouble lon, SpiceDouble lat){
    NObject result(env);

    result.obj().Set("radius", radius);
    result.obj().Set("lon", lon);
    result.obj().Set("lat", lat);

    return result;
}

NObject Packer::pgr(SpiceDouble lon, SpiceDouble lat, SpiceDouble alt){
    NObject result(env);

    result.obj().Set("lon", lon);
    result.obj().Set("lat", lat);
    result.obj().Set("alt", alt);

    return result;
}

NObject Packer::rad(SpiceDouble range, SpiceDouble ra, SpiceDouble dec){
    NObject result(env);

    result.obj().Set("range", range);
    result.obj().Set("ra", ra);
    result.obj().Set("dec", dec);

    return result;
}

NObject Packer::plane(ConstSpicePlane& plane){
    NObject result(env);

    Napi::Array normal = Napi::Array::New(env, 3);
    normal.Set((uint32_t)0, plane.normal[0]);
    normal.Set((uint32_t)1, plane.normal[1]);
    normal.Set((uint32_t)2, plane.normal[2]);
    result.obj().Set("normal", normal);
    result.obj().Set("constant", plane.constant);

    return result;
}

NArrayDouble3 Packer::rec(ConstSpiceDouble (&rectan)[3]){
    return NArrayDouble3(env, rectan);    
}

NArrayInt Packer::ints(const std::vector<SpiceInt>& ints){
    return NArrayInt(env, ints);    
}

NObject Packer::sph(SpiceDouble r, SpiceDouble colat, SpiceDouble slon){
    NObject result(env);

    result.obj().Set("r", r);
    result.obj().Set("colat", colat);
    result.obj().Set("slon", slon);

    return result;
}

NObject Packer::q(ConstSpiceDouble (&q)[4]){
    NObject result(env);

    result.obj().Set("w", q[0]);
    result.obj().Set("x", q[1]);
    result.obj().Set("y", q[2]);
    result.obj().Set("z", q[3]);

    return result;
}

NObject Packer::eul(SpiceDouble angle3, SpiceDouble angle2, SpiceDouble angle1, SpiceInt axis3, SpiceInt axis2, SpiceInt axis1){
    NObject result(env);

    result.obj().Set("angle3", angle3);
    result.obj().Set("angle2", angle2);
    result.obj().Set("angle1", angle1);
    result.obj().Set("axis3",  axis3);
    result.obj().Set("axis2",  axis2);
    result.obj().Set("axis1",  axis1);

    return result;
}

NDouble Packer::et(SpiceDouble et){
    return NDouble(env, et);
}

NDouble Packer::dt(SpiceDouble dt){
    return NDouble(env, dt);
}

NDouble Packer::d(SpiceDouble d){
    return NDouble(env, d);
}

NDouble Packer::dist(SpiceDouble dist){
    return NDouble(env, dist);
}

NInt Packer::i(SpiceInt i){
    return NInt(env, i);
}

NFlag Packer::flag(SpiceBoolean flag){
    return NFlag(env, flag != SPICEFALSE);
}

NArrayDouble3x3 Packer::mat(SpiceDouble (&m)[3][3]){
    return NArrayDouble3x3(env, m);    
}

NArrayDouble6x6 Packer::statemat(SpiceDouble (&m)[6][6]){
    return NArrayDouble6x6(env, m);    
}

NState Packer::state(ConstSpiceDouble (&state)[6]){
    return NState(env, state);    
}

NString Packer::str(ConstSpiceChar* str){
    return NString(env, str);
}

NElts Packer::conics(ConstSpiceDouble (&elts)[8]){
    std::string members[] {"rp", "ecc", "inc", "lnode", "argp", "m0", "t0", "mu"};
    return NElts(env, members, elts);
}

NElts Packer::elms(ConstSpiceDouble (&elms)[10]){
    std::string members[] {"ndt20", "ndd60", "bstar", "incl", "node0", "ecc", "omega", "m0", "n0", "epoch"};
    return NElts(env, members, elms);
}

NElts Packer::geophs(ConstSpiceDouble (&elts)[8]){
    std::string members[] {"j2", "j3", "j4", "ke", "qo", "so", "er", "ae"};
    return NElts(env, members, elts);
}

NArrayWindows Packer::windows(const std::vector<std::pair<double,double>>& cnfine){
    return NArrayWindows(env, cnfine);
}

Packer Pack(const Napi::CallbackInfo& _info){
    return Packer(_info.Env());
}

Packer Pack(Napi::Env _env){
    return Packer(_env);
}
