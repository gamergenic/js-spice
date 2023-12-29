# js-spice

`js-spice` is a Node.js module that provides a JavaScript interface to NASA/JPL/NAIF's CSPICE toolkit, a collection of functions widely used in the planetary science community for spaceflight geometry calculations. Designed primarily for astrophysicists and developers in the field of space exploration, this module enables the integration of CSPICE's robust space mission analysis capabilities into JavaScript applications.

For an example of `js-spice` usage, refer to our web server project that utilizes the module: [Earth-Moon-Sun Simulation](https://github.com/gamergenic/earth-moon-sun). This project illustrates how js-spice can be used for space-related calculations and simulations in a JavaScript environment.

## Ongoing Development Notice

Please note that js-spice is currently under active development. It has not been fully tested and is still evolving. The documentation available at this stage primarily consists of preliminary notes and usage examples. Users are welcome to explore and experiment with the module, but it's important to be aware of its provisional state and ongoing changes.

## Installation Guide

`js-spice` is still in the development phase and has not yet been officially released on npm. To integrate it into your project, you can't currently use the standard npm installation command. Instead, you can include it by linking directly to the GitHub repository as a git submodule. Detailed instructions for this process can be found in the section "Adding js-spice as a git submodule to a host app."

After adding `js-spice` to your project, you'll need to compile the necessary binaries using `node-gyp`, as pre-compiled binaries are not available. This step ensures the module is tailored to your specific platform. Once the build process is complete, it's important to run npm test to verify the build's integrity.

Keep in mind that some tests require SPICE kernel data files, which are automatically downloaded to the test/data directory upon the first test run.


## Usage

```js
const {spice} = require('js-spice');
```
...for just the spice wrapper.

```js
const { spice, cacheGenericKernel, getKernels, getGeophysicalConstants, et_now } = require('js-spice');
```
...to include functions for downloading and caching kernel files, etc.

### Features

`js-spice` is a partial wrapping of the NASA NAIF SPICE toolkit, with additional types that can be used for convenience.  The wrapped functions preserve the documented parameters and usage documented in the official SPICE documentation such that it can be used as a reference source.

### Detailed Documentation

To come.

### API Reference

To come.

#### Types

None.  Native JavaScript types are used.  

Vectors  
`[x,y,z]`, where _*x*_, _*y*_, and _*z*_ are double-precision numerics.

Quaternions  
`{"w":x, "x":x, "y":y, "z":z}`


Ephemeris Time  
`et`, where _*et*_ is a double-precision number.


State  
`{"r": [x,y,z], "v": [dx,dy,dz]}`, where _*x*_, _*y*_, _*z*_ and _*dx*_, _*dy*_, _*dz*_ are double-precision numbers.


AZL  
`{"range": range, "az":az, "el":el};`, where _*range*_, _*az*_, and _*el*_ are double-precision numbers.


CYL  
`{"r": r, "clon":clon, "z":z}`, where _*r*_, _*clon*_, and _*z*_ are double-precision numbers.


GEO  
`{"lon": lon, "lat": lat, "alt": alt}`, where _*lon*_, _*lat*_, and _*alt*_ are double-precision numbers.


LAT  
`{"radius": radius, "lon": lon, "lat": lat}`, where _*radius*_, _*lon*_, and _*lat*_ are double-precision numbers.


PGR  
`{"lon", "lat", "alt"}`, where _*lon*_, _*lat*_, and _*alt*_ are double-precision numbers.


RAD  
`{"range", "ra", "dec"}`, where _*range*_, _*ra*_, and _*dec*_ are double-precision numbers.


SPH  
`{"r", "colat", "slon"}`, where _*r*_, _*colat*_, and _*slon*_ are double-precision numbers.


Osculating elements  
`{"rp": rp, "ecc": ecc, "inc":inc, "lnode":lnode, "argp":argp, "m0":m0, "t0":t0, "mu":mu}`, where all values are double-precision numerics.
```
rp      Perifocal distance.
ecc     Eccentricity.
inc     Inclination.
lnode   Longitude of the ascending node.
argp    Argument of periapse.
m0      Mean anomaly at epoch.
t0      Epoch.
mu      Gravitational parameter.
```


Two-line elements  
`{"ndt20":ndt20, "ndd60":ndd60, "bstar":bstar, "incl":incl, "node0":node0, "ecc":ecc, "omega":omega, "m0":m0, "n0":n0, "epoch":epoch}`, where all values are double-precision numerics


Confinement windows  
`[[start1, end1], [start2, end2], ...]`, where _*start1*_, _*end1*_, ... are double precision et's.


Matrices (3D Rotation)  
```js
[[m00, m01, m02],
 [m10, m11, m12],
 [m20, m21, m22]]
```
Where m00...m22 are double-precision numeric values.


Planes  
`{"normal": [x, y, z], "constant": c}`  


Functions will throw an error when they are unable to decipher input.  The error thrown will explain the expected type for the first incorrect argument detected.
In some places inputs can be provided in multiple formats but outputs formats for a given type are intended to remain consistent.  For example `spice.recazl` will *accept* `([x,y,z])`, `("x":x, "y":y, "z":z)`, or `(x, y, z)` while `spice.azlrec` will only *output* `[x,y,z]`.

#### Functions

Note:  Example usages of js-spice wrappers can be found in the test directory, which is organized by function name.

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


    await getKernels(kernelsToLoad);   

    try{
         /*
        We'll consider Saturn to be visible from DSS-14 when
        Saturn has elevation above 6 degrees in the DSS-14
        topocentric reference frame DSS-14_TOPO. 
        
        Create a confinement window for the view period
        search. This window contains the start and stop times
        of the search interval.
        */
        
        const et0 = et_now();
        const et1 = et_now() + spice.spd() * 5;
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

##### spkezr
https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkezr_c.html

###### Usage
```js
// init js-spice, load kernels
let result = spice.spkezr('moon', new spice.EphemerisTime('Dec 17, 2023, 14:10:00'), 'J2000', 'NONE', 'earth');
console.log(result.toString());
```

##### spkpos
###### Usage
```js
// init js-spice, load kernels
let result = spice.spkpos('moon', new spice.EphemerisTime('Dec 17, 2023, 14:10:00'), 'J2000', 'NONE', 'earth');
```

##### spkgps
###### Usage
```js
// init js-spice, load kernels
let result = spice.spkgps(199, et_now(), "J2000", 399);;
```


##### spkgeo
###### Usage
```js
// init js-spice, load kernels
let result = spice.spkgeo(199, et_now(), "J2000", 399);
```

##### spkcpo
###### Usage
```js
result = spice.spkcpo("mercury", et_now(), "J2000", "OBSERVER", "NONE", [1,1,1], "EARTH", "J2000");
```

##### spkcpt
###### Usage
```js
result = spice.spkcpt([1,1,1], "mercury", "J2000", et_now(), "J2000", "OBSERVER", "NONE", "EARTH");
```

##### spkcvo
###### Usage
```js
result = spice.spkcvo("mercury", et_now(), "J2000", "OBSERVER", "NONE", {r:[1,1,1],v:[0,0,0]}, et_now(), "EARTH", "J2000");
```

##### spkcvt
###### Usage
```js
result = spice.spkcvt({r:[1,1,1],v:[0,0,0]}, et_now(), "mercury", "J2000", et_now(), "J2000", "OBSERVER", "NONE", "EARTH");
```

##### spkw05
###### Usage
```js
let gm = spice.bodvrd("earth", "GM");
let handle = spice.spkopn("myspk.bsp", "myspk", 80);
spice.spkw05(handle, 20580, 399, "J2000", first_et, last_et, "foo", gm, samples);
spice.spkcls(handle);
```

##### timout

###### Usage
```js
console.log(spice.timout(now(), 'MON DD,YYYY  HR:MN:SC.#### (TDB) ::TDB'));
```


### Adding js-spice as a git submodule to a host app

Adding the js-spice module to a host application using Git submodules involves a series of steps. Here's a guide to help you through the process:

#### 1 Initialize the Host Application Repository (If Not Already Done):
* If your host application isn't already a Git repository, initialize it with `git init`.

#### 2 Add the Module as a Submodule:
* Navigate to the root directory of your host application.
* Use the command `git submodule add https://github.com/gamergenic/js-spice.git` to add your module as a submodule.

##### 3 Specify the Path for the Submodule:
* While adding the submodule, you can also specify a path where you want the submodule to be placed. For instance: `git submodule add https://github.com/gamergenic/js-spice.git <desired path>`.
* If you don't specify a path, the submodule will be placed in a directory with the same name as the repository by default.

#### 4 Initialize and Update the Submodule:
* Run `git submodule init` to initialize your submodule.
* Then, run `git submodule update` to fetch all the data from the submodule project and check out the specified commit in your submodule.

#### 5 Commit the Changes in the Host Application:
* After adding the submodule, you will see changes in your host application's repository. These changes include the addition of the `.gitmodules` file and the submodule's directory.
* Commit these changes with `git add .` and `git commit -m "Add js-spice as a submodule"`.

#### 6 Clone the Host Application Along with Submodules:
* If you need to clone the host application repository along with its submodules, use the command `git clone --recurse-submodules <repository URL of host application>`.

#### 7 Update the Submodule:
* To update the js-spice module to the latest commit available in its repository, navigate to the submodule's directory and run `git pull origin master` (or the branch you wish to pull from).
* Then, go back to your host application's root directory and commit the changes.

#### 8 Push the Changes to the Host Application Repository:
* After committing the changes, push them to the host application repository with `git push`.
Remember, each submodule is essentially a separate Git repository, so you need to commit and push changes within each submodule separately, as well as in the host repository.

#### 9 Updating the js-spice module to latest from your host app:
```sh
cd modules/js-spice
git pull origin main
npm install
```

### License
MIT License.
