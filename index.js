const spice = require('./build/Release/spice');
const genericKernels = require('./genericKernels');

function now(){
    const etstr = new Date().toISOString();
    const et = spice.str2et(etstr);
    return et;
}

module.exports = { 
    spice,
    genericKernels,
    now,
}

async function getKernels() {
  // Usage example:
    const leapSeconds = await genericKernels.getGenericKernel('lsk/latest_leapseconds.tls', 'data/naif/generic_kernels/lsk/latest_leapseconds.tls');
    const pck = await genericKernels.getGenericKernel('pck/pck00010.tpc', 'data/naif/generic_kernels/pck/pck00010.tpc');
    const gm = await genericKernels.getGenericKernel('pck/gm_de431.tpc', 'data/naif/generic_kernels/pck/gm_de431.tpc');
    const spk = await genericKernels.getGenericKernel('spk/planets/de430.bsp', 'data/naif/generic_kernels/spk/planets/de430.bsp');

    spice.furnsh(leapSeconds);
    spice.furnsh(pck);
    spice.furnsh(gm);
    spice.furnsh(spk);

    let result = spice.spkpos("mercury", now(), "J2000", "NONE", "earth");
    console.log(JSON.stringify(spice.recrad(result.ptarg)));

    console.log(spice.pi());
    console.log(spice.halfpi());
    console.log(spice.twopi());

    console.log(spice.bodvrd("earth", "GM"));
    console.log(spice.bodvrd("earth", "RADII"));

    console.log(spice.convrt(1, "FEET", "INCHES"));

    console.log(spice.convrt([0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10], "YARDS", "FEET"));
    console.log(spice.azlrec({"range" : 10000, "az" : 2, "el" : -1}, true, true));
    console.log(spice.cylrec({"r" : 10000, "clon" : 2, "z" : -100 }));

    console.log(spice.georec({"lon" : 1, "lat" : -1, "alt" : 1000 }, 10000, 0));
    console.log(spice.latrec({"radius" : 10000, "lon" : 2, "lat" : -1 }));
    console.log(spice.sphrec({"r" : 10000, "colat" : 2, "slon" : -1 }));
    console.log(spice.pgrrec("earth", {"lon" : 1, "lat" : -1, "alt" : 10000 }, 6000, 0));

    console.log(spice.spd());

    console.log(spice.timout(now(), 'MON DD,YYYY  HR:MN:SC.#### (TDB) ::TDB'));

    console.log(spice.dpr());
    console.log(spice.rpd());

    spice.unload(leapSeconds);
    spice.unload(pck);
    spice.unload(gm);
    spice.unload(spk);
}

getKernels();

try{
    spice.errprt('set', 'short');
    spice.errdev('set', 'null');
    spice.erract('set', 'return');
}
catch(error){
    console.error('error: ', error);
}

