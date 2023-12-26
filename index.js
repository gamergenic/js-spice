const spice = require('./build/Release/js-spice');
const genericKernels = require('./genericKernels');
const geophysical = require('./geophysical');

function et_now(){
    const etstr = new Date().toISOString();
    const et = spice.str2et(etstr);
    return et;
}

try{
    spice.errprt('set', 'short');
    spice.errdev('set', 'null');
    spice.erract('set', 'return');
}
catch(error){
    console.error('error: ', error);
}


module.exports = { 
    spice,
    genericKernels,
    et_now,
    geophysical
}


console.log("---mxm, mxv---");
try {
    let elts = {"rp":6000, "ecc":0.1, "inc":0.1, "lnode":0.1, "argp":0.1, "m0":0.1, "t0":555, "mu":22222 };
    let foo = spice.conics(elts, 3333);
    console.log(JSON.stringify(foo));
    let newelts = spice.oscelt(foo, 3333, 22222);
    console.log(JSON.stringify(newelts));
    foo = spice.conics(newelts, 3333);
    console.log(JSON.stringify(foo));

    let m1 = [[1, 0, 0], [0, 1, 0], [0, 0, 1]];
    let m2 = [[0, 1, 0], [-1, 0, 0], [0, 0, 1]];
    let m3 = spice.mxm(m1, m2);
    console.log(JSON.stringify(m3));
    let m4 = spice.invert(m2);
    console.log(JSON.stringify(m4));

    let v1 = [1, 0, 0];
    let v2 = spice.mxv(m3, v1);
    console.log(JSON.stringify(v2));
    console.log(JSON.stringify(spice.vadd(v1,v2)));
    console.log(JSON.stringify(spice.vcrss(v1,[0,1,0])));
    console.log(JSON.stringify(spice.vdot(v1,v2)));
    console.log(JSON.stringify(spice.vdist(v1,[0,1,0])));
    console.log(JSON.stringify(spice.vhat(v1)));
    console.log(JSON.stringify(spice.vnorm(v1)));
    console.log(JSON.stringify(spice.clight()));
    console.log(JSON.stringify(spice.j1900()));
    console.log(JSON.stringify(spice.j1950()));
    console.log(JSON.stringify(spice.j2000()));
    console.log(JSON.stringify(spice.j2100()));
    console.log(JSON.stringify(spice.jyear()));
    console.log(JSON.stringify(spice.b1900()));
    console.log(JSON.stringify(spice.b1950()));
    

    console.log("---ident---");
    let ident = spice.ident();
    console.log(JSON.stringify(ident));

    let m5 = [[1, 2, 3], [4, 5, 6], [7, 8, 9]];
    console.log(JSON.stringify(spice.xpose(m5)));
}
catch (error) {
    console.error(error);
}

async function getKernels() {
  // Usage example:
    // const leapSeconds = await genericKernels.getGenericKernel('lsk/latest_leapseconds.tls', 'data/naif/generic_kernels/lsk/latest_leapseconds.tls');
    // const pck = await genericKernels.getGenericKernel('pck/pck00010.tpc', 'data/naif/generic_kernels/pck/pck00010.tpc');
    // const gm = await genericKernels.getGenericKernel('pck/gm_de431.tpc', 'data/naif/generic_kernels/pck/gm_de431.tpc');
    // const spk = await genericKernels.getGenericKernel('spk/planets/de430.bsp', 'data/naif/generic_kernels/spk/planets/de430.bsp');

    const kernelsToLoad = [
        'lsk/a_old_versions/naif0009.tls',
        'pck/a_old_versions/pck00008.tpc',
        'spk/planets/a_old_versions/de421.bsp',
        'spk/satellites/a_old_versions/sat288.bsp',
        'spk/stations/a_old_versions/earthstns_itrf93_050714.bsp',
        'fk/stations/a_old_versions/earth_topo_050714.tf',
        'pck/a_old_versions/earth_070425_370426_predict.bpc'
    ];


    async function loadAndProcessFiles(files) {
        const operations = files.map(file => {
            return genericKernels.getGenericKernel(file, `data/naif/generic_kernels/${file}`).then(kernel => {
                spice.furnsh(kernel);
            });
        });
    
        await Promise.all(operations);
        console.log("done loading kernels");
    }
    await loadAndProcessFiles(kernelsToLoad);

    let tle = [
        "1 43908U 18111AJ  20146.60805006  .00000806  00000-0  34965-4 0  9999",
        "2 43908  97.2676  47.2136 0020001 220.6050 139.3698 15.24999521 78544"
    ];
    console.log('---tle---')
    const rslt = spice.getelm(1957, tle);
    const elems = rslt.elems;
    console.log(JSON.stringify(elems));
    console.log('///tle---')

    const geophs = await geophysical.getGeophysicalConstants(true);
    console.log(JSON.stringify(geophs));
    console.log(JSON.stringify(elems));
    console.log(spice.evsgp4(spice.str2et('2020-05-26 02:25:00'), geophs, elems));

    
    console.log(JSON.stringify(spice.deltet(100,"UTC")));
    console.log(JSON.stringify(spice.et2utc(spice.jyear(),"ISOC", 5)));
    console.log(JSON.stringify(spice.etcal(spice.jyear())));
       
    console.log(JSON.stringify(spice.recrad(1,1,1)));
    console.log("---azlrec---");
    try{ console.log(JSON.stringify(spice.azlrec()))} catch (error) { console.error(error);};
    console.log("---2---");
    try{ console.log(JSON.stringify(spice.azlrec(1)))} catch (error) { console.error(error);};
    console.log("---3---");
    try{ console.log(JSON.stringify(spice.azlrec({},{})))} catch (error) { console.error(error);};
    console.log("---4---");
    try{ console.log(JSON.stringify(spice.azlrec({range:1, az:1, el:1}, true, true)))} catch (error) { console.error(error);};
    console.log("---cylrec---");
    try{ console.log(JSON.stringify(spice.cylrec()))} catch (error) { console.error(error);};
    console.log("---georec---");
    try{ console.log(JSON.stringify(spice.georec()))} catch (error) { console.error(error);};
    console.log("---pgrrec---");
    try{ console.log(JSON.stringify(spice.pgrrec()))} catch (error) { console.error(error);};
    console.log("---radrec---");
    try{ console.log(JSON.stringify(spice.radrec()))} catch (error) { console.error(error);};
    console.log("---sphrec---");
    try{ console.log(JSON.stringify(spice.sphrec()))} catch (error) { console.error(error);};
    console.log("---recazl---");
    try{ console.log(JSON.stringify(spice.recazl()))} catch (error) { console.error(error);};
    console.log("---reccyl---");
    try{ console.log(JSON.stringify(spice.reccyl()))} catch (error) { console.error(error);};
    console.log("---recgeo---");
    try{ console.log(JSON.stringify(spice.recgeo()))} catch (error) { console.error(error);};
    console.log("---reclat---");
    try{ console.log(JSON.stringify(spice.reclat()))} catch (error) { console.error(error);};
    console.log("---recpgr---");
    try{ console.log(JSON.stringify(spice.recpgr()))} catch (error) { console.error(error);};
    console.log("---recrad---");
    try{ console.log(JSON.stringify(spice.recrad()))} catch (error) { console.error(error);};
    console.log("---recsph---");
    try{ console.log(JSON.stringify(spice.recsph()))} catch (error) { console.error(error);};

    console.log("---convrt---");
    try{ console.log(JSON.stringify(spice.convrt(1, "STATUTE_MILES", "FEET")))} catch (error) { console.error(error);};

    // console.log("---convrt---");
    // try{
    //     console.log(JSON.stringify(spice.convrt(1)))
    // }
    // catch (error) {
    //     console.error(error);
    // };
    console.log("---axisar---");
    try{ console.log(JSON.stringify(spice.axisar([0,1,0],spice.halfpi())))} catch (error) { console.error(error);};
    console.log("---axisar---");
    try{ console.log(JSON.stringify(spice.axisar()))} catch (error) { console.error(error);};
    
    console.log("---mxm, mxv---");
    try{
        let m1 = [[1,0,0],[0,1,0],[0,0,1]];
        let m2 = [[1,0,0],[0,1,0],[0,0,1]];
        let m3 = spice.mxm(m1, m2);
        console.log(JSON.stringify(m3));

        let v1 = [1,0,0];
        let v2 = spice.mxv(m3, v1);
        console.log(JSON.stringify(v2));
    }
    catch(error){
        console.error(error);
    }

    
    // spice.furnsh(leapSeconds);
    // spice.furnsh(pck);
    // spice.furnsh(gm);
    // spice.furnsh(spk);

    console.log('---spkpos---');
    let result = spice.spkpos("mercury", et_now(), "J2000", "NONE", "earth");
    console.log('---result---');
    console.log(JSON.stringify(result));

    // console.log(JSON.stringify(spice.recrad(result.ptarg)));

    // console.log(spice.pi());
    // console.log(spice.halfpi());
    // console.log(spice.twopi());

    // console.log(spice.bodvrd("earth", "GM"));
    // console.log(spice.bodvrd("earth", "RADII"));

    // console.log(spice.convrt(1, "FEET", "INCHES"));

    // console.log(spice.convrt([0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10], "YARDS", "FEET"));
    // console.log(spice.azlrec({"range" : 10000, "az" : 2, "el" : -1}, true, true));
    // console.log(spice.cylrec({"r" : 10000, "clon" : 2, "z" : -100 }));

    // console.log(spice.georec({"lon" : 1, "lat" : -1, "alt" : 1000 }, 10000, 0));
    // console.log(spice.latrec({"radius" : 10000, "lon" : 2, "lat" : -1 }));
    // console.log(spice.sphrec({"r" : 10000, "colat" : 2, "slon" : -1 }));
    // console.log(spice.pgrrec("earth", {"lon" : 1, "lat" : -1, "alt" : 10000 }, 6000, 0));

    // console.log(spice.spd());

    // console.log(spice.timout(et_now(), 'MON DD,YYYY  HR:MN:SC.#### (TDB) ::TDB'));

    // console.log(spice.dpr());
    // console.log(spice.rpd());

    try{
         /*
        We'll consider Saturn to be visible from DSS-14 when
        Saturn has elevation above 6 degrees in the DSS-14
        topocentric reference frame DSS-14_TOPO. 
        
        Create a confinement window for the view period
        search. This window contains the start and stop times
        of the search interval.
        */
        
        const et0 = spice.str2et("2009 JAN 1");
        const et1 = spice.str2et("2009 JAN 5");
        const cnfine = [[et0, et1]];

        /*
          Set the observer, target and reference frame.
          */
        const obsrvr = "DSS-14";
        const target = "SUN";
        const frame  = "DSS-14_TOPO";

        /*
        The coordinate system is latitudinal; in this system,
        in the DSS-14_TOPO frame, the coordinate "latitude"
        is equivalent to elevation.
        */
        const crdsys = "LATITUDINAL";
        const coord  = "LATITUDE";

        /*
        The relational operator for this search is "greater
        than" and the reference value is 6 degrees (converted
        to radians).
        */
        const relate = ">";
        const refval = 6.0 * spice.rpd();

        /*
        
        We're looking for the apparent position of Saturn,
        so apply corrections for light time and stellar
        aberration.
        */
        const abcorr = "LT+S";

        /*
        Set the step size for this search. The step must
        be shorter than the shortest interval over which
        the elevation is increasing or decreasing.
        We pick a conservative value: 6 hours. Units
        expected by SPICE are TDB seconds.
        */
        const step   =  spice.spd() / 4;

        /*
        The adjustment value isn't used for this search;
        set it to 0.
        */
        const adjust = 0.0;

        /*
        The number of intervals will be left as default
        and the argument omitted.
    
        Execute the search.
        */        
        console.log("\n\nStarting elevation search.\n");

        const result = spice.gfposc(
            target, frame, abcorr, obsrvr,
            crdsys, coord, relate, refval,
            adjust, step,  cnfine);

        console.log("Done.\n");

        /*
        Display the times of rise and set.
        */
        console.log( "\nTimes of Sun rise/set as seen from DSS-14:\n\n" );

        const timeformat = "YYYY MON DD HR:MN:SC.###### TDB::RND::TDB";
        if(Array.isArray(result)){
            result.forEach((window)=>{
                et0str = spice.timout(window[0], timeformat);
                et1str = spice.timout(window[1], timeformat);
                console.log(`${et0str} ${et1str}`);
            });
        }
    }
    catch(error){
        console.error(error);
    }

    // spice.unload(leapSeconds);
    // spice.unload(pck);
    // spice.unload(gm);
    // spice.unload(spk);
}

getKernels();


