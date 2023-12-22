const spice = require('./build/Release/spice');
const genericKernels = require('./genericKernels');

module.exports = { 
    spice,
    genericKernels
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
}

// getKernels();

let foo = new spice.DistanceVector(0,0,0);

const foostr = foo.toString();
console.log(foostr);

return;

try{
    spice.errprt('set', 'short');
    spice.errdev('set', 'null');
    spice.erract('set', 'return');
}
catch(error){
    console.error('error: ', error);
}


const oneKM = new spice.Distance.fromKilometers(1);
console.log(spice.Distance.isA(oneKM));                        // logs 'true'
console.log(spice.Distance.isA({"km": 0}));                    // logs 'false'

const newVector = new spice.DistanceVector();
console.log(spice.DistanceVector.isA(newVector));               // logs 'true'
console.log(spice.Distance.isA(newVector));                     // logs 'false'
console.log(spice.Distance.isA(newVector.getX()));              // logs 'true'

console.log(newVector.toString());

try{
    spice.furnsh("D:\\gameassets\\naif\\kernels\\Generic\\LSK\\latest_leapseconds.tls");
    spice.furnsh("D:\\gameassets\\naif\\kernels\\Generic\\SPK\\planets\\de430.bsp");
    spice.furnsh("D:\\gameassets\\naif\\kernels\\Generic\\PCK\\gm_de431.tpc");
    spice.furnsh("D:\\gameassets\\naif\\kernels\\Generic\\PCK\\pck00010.tpc");

    let v = new spice.DistanceVector(1);
    console.log(v);

    let et = new spice.EphemerisTime('Dec 17, 2023, 14:10:00');
    console.log(et.toString('C'));
    let result = spice.spkpos('moon', et, 'J2000', 'NONE', 'earth');
    console.log(JSON.stringify(result));

    const oneSecond = new spice.EphemerisPeriod.fromSeconds(1);
    const oneMinute = new spice.EphemerisPeriod.fromMinutes(1);
    const oneHour = new spice.EphemerisPeriod.fromHours(1);
    const oneDay = new spice.EphemerisPeriod.fromDays(1);
    const oneYear = new spice.EphemerisPeriod.fromYears(1);
    const oneJulianYear = new spice.EphemerisPeriod.fromJulianYears(1);
    const oneTropicalYear = new spice.EphemerisPeriod.fromTropicalYears(1);
    console.log(oneTropicalYear.getTropicalYears()); // logs '1'
    console.log(oneTropicalYear.getJulianYears());   // logs '0.9999786414784394'
    console.log(oneTropicalYear.getYears());         // logs '0.9999786414784394'
    console.log(oneTropicalYear.getDays());          // logs '365.2421988'
    console.log(oneTropicalYear.getHours());         // logs '8765.812771199999'
    console.log(oneTropicalYear.getMinutes());       // logs '525948.7662719999'
    console.log(oneTropicalYear.getSeconds());       // logs '31556925.97632'

let dt = new spice.EphemerisPeriod(0);
dt.setYears(1);

    const et1 = new spice.EphemerisTime(0);
    const et2 = new spice.EphemerisTime('2023-12-17T07:48:00');
    
    console.log(et1.toString());            // logs '0.000000'
    console.log(et1.toString('C'));         // logs '2000 JAN 01 11:58:56'
    console.log(et2.toString());            // logs '756071349.183489'
    console.log(et2.toString('ISOC', 14));  // logs '2023-12-17T07:48:00.0000000000000'
    
    const et2jsonstr = JSON.stringify(et2);
    console.log(et2jsonstr);                // logs '{"et":756071349.1834894}'
    
    const et2json = JSON.parse(et2jsonstr);
    const et3 = spice.EphemerisTime.fromJson(et2json);
    
    console.log(et3.toString('C'));         // logs '2023 DEC 17 07:48:00'
    // Time + Period = Time
    const et4 = et2.add(new spice.EphemerisPeriod.fromDays(1));
    console.log(et4.toJSON());              // { et: 756157749.1834894 }
    const et5 = et2.add(new spice.EphemerisPeriod.fromDays(1));
    console.log(et5.toString('C'));         // logs '2023 DEC 18 07:48:00'
    const et6 = et2.add({"dt" : 60*60*24 });
    console.log(et6.toString('C'));         // logs '2023 DEC 18 07:48:00'
    console.log("?");    
    
    // Time - Time = Period
    const dt1 = et5.subtract(et2);
    console.log(JSON.stringify(dt1));       // logs '{"dt":86400}'
    console.log("!");    
    
    // Time - Period = Time
    const et7 = et5.subtract(dt1);
    console.log(JSON.stringify(et7));       // logs '{"et":756071349.1834894}'    

    spice.unload("D:\\gameassets\\naif\\kernels\\Generic\\LSK\\latest_leapseconds.tls");
    spice.unload("D:\\gameassets\\naif\\kernels\\Generic\\SPK\\planets\\de430.bsp");
    spice.unload("D:\\gameassets\\naif\\kernels\\Generic\\PCK\\gm_de431.tpc");
    spice.unload("D:\\gameassets\\naif\\kernels\\Generic\\PCK\\pck00010.tpc");
}
catch(error){
    console.error('error: ', error);
}



