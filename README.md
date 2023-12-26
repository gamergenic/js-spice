# js-spice

javascript wrapper for NASA/NAIF SPICE spaceflight geometry toolkit

## Installation

```bash
npm install js-spice
```

## Usage

```js
const spice = require('js-spice');
```

### Features

js-spice is a partial wrapping of the NASA NAIF SPICE toolkit, with additional types that can be used for convenience.  The wrapped functions preserve the documented parameters and usage documented in the official SPICE documentation such that it can be used as a reference source.

### Detailed Documentation

### API Reference

#### Types

##### EphemerisTime

```js
const spice = require('js-spice');

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

// Time - Time = Period
const dt1 = et5.subtract(et2);
console.log(JSON.stringify(dt1));       // logs '{"dt":86400}'

// Time - Period = Time
const et7 = et5.subtract(dt1);
console.log(JSON.stringify(et7));       // logs '{"et":756071349.1834894}'


```


##### EphemerisPeriod

```js
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
```


```js
console.log(oneMinute.add(oneSecond).toString());                   // logs '61'
console.log(oneMinute.add({"dt" : -1}).toString());                 // logs '59'
console.log(oneMinute.add(1).toString());                           // logs '61'
console.log(oneMinute.subtract(oneSecond).toString());              // logs '59'
console.log(oneMinute.multiply(2).toString());                      // logs '120.000000'
console.log(oneMinute.divide(oneSecond));                           // logs '60'
const seventyFiveSeconds = oneMinute.multiply(1.25);
console.log(seventyFiveSeconds.mod(oneMinute).toString());          // logs '15.000000'
console.log(seventyFiveSeconds.mod({"dt" : 60}).toString());        // logs '15.000000'
```

```js
// EphemerisPeriod/EphemerisPeriod = dimensionless scalar
console.log(JSON.stringify(oneMinute.divide({"dt" : 60})));   // logs '1'
// EphemerisPeriod/dimensionless scalar = EphemerisPeriod
console.log(JSON.stringify(oneMinute.divide(60)));   // logs '{"dt":1}'
```

##### Distance
```js
let distance = new spice.Distance.fromKilometers(1);
let meters = new spice.Distance.getMeters();
distance.setMeters(1000);
```

```js
const oneMM = new spice.Distance.fromMillimeters(1);
const oneCM = new spice.Distance.fromCentimeters(1);
const oneM = new spice.Distance.fromMeters(1);
const oneKM = new spice.Distance.fromKilometers(1);
const oneInch = new spice.Distance.fromInches(1);
const oneFoot = new spice.Distance.fromFeet(1);
const oneYard = new spice.Distance.fromYards(1);
const oneStatuteMile = new spice.Distance.fromStatuteMiles(1);
const oneNauticalMile = new spice.Distance.fromNauticalMiles(1);
const oneAU = new spice.Distance.fromAstronomicalUnits(1);
const oneParsec = new spice.Distance.fromParsecs(1);
const oneLightSec = new spice.Distance.fromLightSeconds(1);
const oneLightYear = new spice.Distance.fromLightYears(1);
console.log(oneParsec.getLightYears());              // logs '3.261563775298437'
console.log(oneLightYear.getLightSeconds());         // logs '31557600'
console.log(oneLightYear.getParsecs());              // logs '0.3066013939612445'
console.log(oneLightYear.getAstronomicalUnits());    // logs '63241.077120753485'
console.log(oneAU.getNauticalMiles());               // logs '80776388.02035037'
console.log(oneNauticalMile.getStatuteMiles());      // logs '1.1507794480235425'
console.log(oneStatuteMile.getYards());              // logs '1760'
console.log(oneStatuteMile.getFeet());               // logs '5280'
console.log(oneFoot.getInches());                    // logs '12.000000000000002'
console.log(oneStatuteMile.getKilometers());         // logs '1.609344'
console.log(oneKM.getMeters());                      // logs '1000'
console.log(oneKM.getCentimeters());                 // logs '100000'
console.log(oneKM.getMillimeters());                 // logs '1000000'
```

```js
console.log(oneKM.add(oneM).toString());                        // logs '1.001'
console.log(oneKM.add({"km" : -0.001 }).toString());            // logs '0.999'
console.log(oneKM.add(1).toString());                           // logs '2.000000'
console.log(oneKM.subtract(oneM).toString());                   // logs '0.999'
console.log(oneKM.multiply(2).toString());                      // logs '2.000000'
console.log(oneKM.divide(oneM));                                // logs '1000'
const seventyFiveMeters = new spice.Distance.fromMeters(75);
const fiftyMeters = new spice.Distance.fromMeters(50);
console.log(seventyFiveMeters.mod(fiftyMeters).toString());     // logs '0.025000'
console.log(seventyFiveMeters.mod({"km" : 0.01}).toString());   // logs '0.005000'
```

```js
console.log(spice.Distance.isA(oneKM));                        // logs 'true'
console.log(spice.Distance.isA({"km";}));                      // logs 'false'
```

##### DistanceVector

```js
const newVector = new spice.DistanceVector();
console.log(spice.DistanceVector.isA(newVector));               // logs 'true'
console.log(spice.Distance.isA(newVector));                     // logs 'false'
console.log(spice.Distance.isA(newVector.getX()));              // logs 'true'
```

#### Functions

# pi
    console.log(spice.pi());

# halfpi
    console.log(spice.halfpi());
    console.log(spice.twopi());

# twopi

# bodvrd
    console.log(spice.bodvrd("earth", "GM"));
    console.log(spice.bodvrd("earth", "RADII"));

# convrt
    console.log(spice.convrt(1, "FEET", "INCHES"));
    console.log(spice.convrt([0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10], "YARDS", "FEET"));

# azlrec
    console.log(spice.azlrec({"range" : 10000, "az" : 2, "el" : -1}, true, true));

# cylrec
    console.log(spice.cylrec({"r" : 10000, "clon" : 2, "z" : -100 }));

# georec
    console.log(spice.georec({"lon" : 1, "lat" : -1, "alt" : 1000 }, 10000, 0));

# latrec
    console.log(spice.latrec({"radius" : 10000, "lon" : 2, "lat" : -1 }));

# sphrec
    console.log(spice.sphrec({"r" : 10000, "colat" : 2, "slon" : -1 }));

# pgrrec
    console.log(spice.pgrrec("earth", {"lon" : 1, "lat" : -1, "alt" : 10000 }, 6000, 0));

##### erract

###### Usage
```js
const spice = require('js-spice');
spice.erract('set', 'return');
```

##### errdev

###### Usage
```js
const spice = require('js-spice');
spice.errdev('set', 'null');
```

##### errprt

###### Usage
```js
const spice = require('js-spice');
spice.errprt('set', 'short');
```

##### furnsh

###### Usage
```js
const spice = require('js-spice');
spice.furnsh("C:\\naif\\kernels\\Generic\\LSK\\latest_leapseconds.tls");
```


##### gfposc

###### example

From:
https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/gf.html#Natural%20satellite%20occultation%20or%20transit


```js
    const kernelsToLoad = [
        'lsk/a_old_versions/naif0009.tls',
        'pck/a_old_versions/pck00008.tpc',
        'spk/planets/a_old_versions/de421.bsp',
        'spk/satellites/a_old_versions/sat288.bsp',
        'spk/stations/a_old_versions/earthstns_itrf93_050714.bsp',
        'fk/stations/a_old_versions/earth_topo_050714.tf',
        'pck/a_old_versions/earth_070425_370426_predict.bpc',
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

    try{
         /*
        We'll consider Saturn to be visible from DSS-14 when
        Saturn has elevation above 6 degrees in the DSS-14
        topocentric reference frame DSS-14_TOPO. 
        
        Create a confinement window for the view period
        search. This window contains the start and stop times
        of the search interval.
        */
        
        const et0 = now();
        const et1 = now() + spice.spd() * 5;
        const cnfine = [[et0, et1]];

        /*
          Set the observer, target and reference frame.
          */
        const obsrvr = "DSS-14";
        const target = "SATURN";
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
        console.log( "\nTimes of Saturn rise/set as seen from DSS-14:\n\n" );

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
```

##### evpsg4

https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/getelm_c.html

###### Usage

```js
const {spice, geophysical} = require('js-spice');

const tles = [
        "1 43908U 18111AJ  20146.60805006  .00000806  00000-0  34965-4 0  9999",
        "2 43908  97.2676  47.2136 0020001 220.6050 139.3698 15.24999521 78544"
    ];
// use spice to parse the tle data into useable form (epoch and elements are returned as 'epoch' and 'elems')
const getelm_result = spice.getelm(1957, tles);
const elems = getelm_result.elems;

// download https://naif.jpl.nasa.gov/pub/naif/generic_kernels/pck/geophysical.ker if necessary and furnsh it
const geophs = await geophysical.getGeophysicalConstants(true);

const stateVector = spice.evsgp4(spice.str2et('2020-05-26 02:25:00'), geophs, elems);

console.log(JSON.stringify(stateVector));
```

##### unload
###### Usage
```js
const spice = require('js-spice');
spice.unload("C:\\naif\\kernels\\Generic\\LSK\\latest_leapseconds.tls");
```

##### str2et
###### Usage
```js
const spice = require('js-spice');
spice.unload("C:\\naif\\kernels\\Generic\\LSK\\latest_leapseconds.tls");
```

##### spkpos
###### Usage
```js
// init js-spice, load kernels
let result = spice.spkpos('moon', new spice.EphemerisTime('Dec 17, 2023, 14:10:00'), 'J2000', 'NONE', 'earth');
console.log(result.toString());
```

##### timout

console.log(spice.timout(now(), 'MON DD,YYYY  HR:MN:SC.#### (TDB) ::TDB'));

### License
MIT License.
