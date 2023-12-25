#include "utility/pack.h"

Packer::Packer(Napi::Env _env) : env(_env) {
}


NObject Packer::azl(SpiceDouble range, SpiceDouble az, SpiceDouble el){
    Napi::HandleScope scope(env);
    NObject result(env);

    result.obj().Set("range", range);
    result.obj().Set("az", az);
    result.obj().Set("el", el);

    return result;
}

NObject Packer::cyl(SpiceDouble r, SpiceDouble clon, SpiceDouble z){
    Napi::HandleScope scope(env);
    NObject result(env);

    result.obj().Set("r", r);
    result.obj().Set("clon", clon);
    result.obj().Set("z", z);

    return result;
}

NObject Packer::geo(SpiceDouble lon, SpiceDouble lat, SpiceDouble alt){
    Napi::HandleScope scope(env);
    NObject result(env);

    result.obj().Set("lon", lon);
    result.obj().Set("lat", lat);
    result.obj().Set("alt", alt);

    return result;
}

NObject Packer::lat(SpiceDouble radius, SpiceDouble lon, SpiceDouble lat){
    Napi::HandleScope scope(env);
    NObject result(env);

    result.obj().Set("radius", radius);
    result.obj().Set("lon", lon);
    result.obj().Set("lat", lat);

    return result;
}

NObject Packer::pgr(SpiceDouble lon, SpiceDouble lat, SpiceDouble alt){
    Napi::HandleScope scope(env);
    NObject result(env);

    result.obj().Set("lon", lon);
    result.obj().Set("lat", lat);
    result.obj().Set("alt", alt);

    return result;
}

NObject Packer::rad(SpiceDouble range, SpiceDouble ra, SpiceDouble dec){
    Napi::HandleScope scope(env);
    NObject result(env);

    result.obj().Set("range", range);
    result.obj().Set("ra", ra);
    result.obj().Set("dec", dec);

    return result;
}

NArrayDouble3 Packer::rec(ConstSpiceDouble (&rectan)[3]){
    Napi::HandleScope scope(env);
    return NArrayDouble3(env, rectan);    
}

NObject Packer::sph(SpiceDouble r, SpiceDouble colat, SpiceDouble slon){
    Napi::HandleScope scope(env);
    NObject result(env);

    result.obj().Set("r", r);
    result.obj().Set("colat", colat);
    result.obj().Set("slon", slon);

    return result;
}

NDouble Packer::et(SpiceDouble et){
    Napi::HandleScope scope(env);
    return NDouble(env, et);
}

NDouble Packer::dt(SpiceDouble dt){
    Napi::HandleScope scope(env);
    return NDouble(env, dt);
}

NDouble Packer::d(SpiceDouble d){
    Napi::HandleScope scope(env);
    return NDouble(env, d);
}

NDouble Packer::dist(SpiceDouble dist){
    Napi::HandleScope scope(env);
    return NDouble(env, dist);
}

NInt Packer::i(SpiceInt i){
    Napi::HandleScope scope(env);
    return NInt(env, i);
}

NFlag Packer::flag(SpiceBoolean flag){
    Napi::HandleScope scope(env);
    return NFlag(env, flag != SPICEFALSE);
}

NArrayDouble3x3 Packer::mat(SpiceDouble (&m)[3][3]){
    Napi::HandleScope scope(env);
    return NArrayDouble3x3(env, m);    
}

NState Packer::state(ConstSpiceDouble (&state)[6]){
    Napi::HandleScope scope(env);
    return NState(env, state);    
}

NString Packer::str(ConstSpiceChar* str){
    Napi::HandleScope scope(env);
    return NString(env, str);
}

NElts Packer::conics(ConstSpiceDouble (&elts)[8]){
    Napi::HandleScope scope(env);
    std::string members[] {"rp", "ecc", "inc", "lnode", "argp", "m0", "t0", "mu"};
    return NElts(env, members, elts);
}

Packer Pack(const Napi::CallbackInfo& _info){
    return Packer(_info.Env());
}

Packer Pack(Napi::Env _env){
    return Packer(_env);
}
