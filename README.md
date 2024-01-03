# js-spice

`js-spice` is a Node.js module that provides a JavaScript interface to NASA/JPL/NAIF's CSPICE toolkit, a collection of functions widely used in the planetary science community for spaceflight geometry calculations. Designed primarily for astrophysicists and developers in the field of space exploration, this module enables the integration of CSPICE's robust space mission analysis capabilities into JavaScript applications.

For an example of `js-spice` usage, refer to our web server project that utilizes the module: [Earth-Moon-Sun Simulation](https://github.com/gamergenic/earth-moon-sun). This project illustrates how js-spice can be used for space-related calculations and simulations in a JavaScript environment.

## Installation Guide

To install js-spice to your node.js project:
`npm install @gamergenic/js-spice`

### Tests
`js-spice` can be tested to verify the build's integrity by navigating to the project's directory and executing `npm test`.

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

### Example

An example of using SPICE from JavaScript:
```js

async function example(){
    const { spice, getKernels } = require('js-spice');

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
}

// run the asynchronous example.
// the example will download and cache kernel files, then use 'gfposc' to determine
// Saturn's rise/set time as seen from DSS-14.
example();
```

### Features

`js-spice` is a partial wrapping of the NASA NAIF SPICE toolkit, with additional types that can be used for convenience.  The wrapped functions preserve the documented parameters and usage documented in the official SPICE documentation such that it can be used as a reference source.

### API Reference

#### Functions

Wrapped function list:  

[axisar](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/axisar_c.html)  
[azlrec](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/azlrec_c.html)  
[b1900](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/b1900_c.html)  
[b1950](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/b1950_c.html)  
[bodvrd](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/bodvrd_c.html)  
[clight](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/clight_c.html)  
[conics](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/conics_c.html)  
[convrt](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/convrt_c.html)  
[cylrec](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/cylrec_c.html)  
[deltet](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/deltet_c.html)  
[dpr](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/dpr_c.html)  
[erract](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/erract_c.html)  
[errdev](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/errdev_c.html)  
[errprt](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/errprt_c.html)  
[et2utc](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/et2utc_c.html)  
[etcal](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/etcal_c.html)  
[eul2m](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/eul2m_c.html)  
[evsgp4](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/evsgp4_c.html)  
[failed](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/failed_c.html)  
[furnsh](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/furnsh_c.html)  
[georec](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/georec_c.html)  
[getelm](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/getelm_c.html)  
[gfposc](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/gfposc_c.html)  
[gfsep](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/gfsep_c.html)  
[halfpi](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/halfpi_c.html)  
[ident](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/ident_c.html)  
[invert](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/invert_c.html)  
[j1900](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/j1900_c.html)  
[j1950](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/j1950_c.html)  
[j2000](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/j2000_c.html)  
[j2100](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/j2100_c.html)  
[jyear](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/jyear_c.html)  
[kclear](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/kclear_c.html)  
[latrec](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/latrec_c.html)  
[m2eul](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/m2eul_c.html)  
[m2q](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/m2q_c.html)  
[mtxm](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/mtxm_c.html)  
[mtxv](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/mtxv_c.html)  
[mxm](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/mxm_c.html)  
[mxmt](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/mxmt_c.html)  
[mxv](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/mxv_c.html)  
[nvc2pl](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/nvc2pl_c.html)  
[nvp2pl](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/nvp2pl_c.html)  
[oscelt](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/oscelt_c.html)  
[pckfrm](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/pckfrm_c.html)  
[pgrrec](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/pgrrec_c.html)  
[pi](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/pi_c.html )  
[pl2nvc](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/pl2nvc_c.html)  
[pl2nvp](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/pl2nvp_c.html)  
[pl2psv](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/pl2psv_c.html)  
[prop2b](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/prop2b_c.html)  
[psv2pl](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/psv2pl_c.html)  
[pxform](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/pxform_c.html)  
[pxfrm2](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/pxfrm2_c.html)  
[q2m](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/q2m_c.html)  
[qxq](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/qxq_c.html)  
[radrec](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/radrec_c.html)  
[raxisa](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/raxisa_c.html)  
[recazl](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/recazl_c.html)  
[reccyl](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/reccyl_c.html)  
[recgeo](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/recgeo_c.html)  
[reclat](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/reclat_c.html)  
[recpgr](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/recpgr_c.html)  
[recrad](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/recrad_c.html)  
[recsph](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/recsph_c.html)  
[reset](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/reset_c.html)  
[rotate](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/rotate_c.html)  
[rpd](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/rpd_c.html)  
[sigerr](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/sigerr_c.html)  
[spd](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spd_c.html)  
[sphrec](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/sphrec_c.html)  
[spkcls](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkcls_c.html)  
[spkcpo](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkcpo_c.html)  
[spkcpt](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkcpt_c.html)  
[spkcvo](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkcvo_c.html)  
[spkcvt](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkcvt_c.html)  
[spkezr](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkezr_c.html)  
[spkgeo](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkgeo_c.html)  
[spkgps](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkgps_c.html)  
[spkobj](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkobj_c.html)  
[spkopn](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkopn_c.html)  
[spkpos](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkpos_c.html)  
[spkw05](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkw05_c.html)  
[str2et](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/str2et_c.html)  
[sxform](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/sxform_c.html)  
[timout](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/timout_c.html)  
[twopi](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/twopi_c.html)  
[unload](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/unload_c.html)  
[vadd](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vadd_c.html)  
[vcrss](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vcrss_c.html)  
[vdist](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vdist_c.html)  
[vdot](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vdot_c.html)  
[vequ](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vequ_c.html)  
[vhat](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vhat_c.html)  
[vlcom](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vlcom_c.html)  
[vlcom3](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vlcom3_c.html)  
[vminus](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vminus_c.html)  
[vnorm](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vnorm_c.html)  
[vpack](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vpack_c.html)  
[vperp](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vperp_c.html)  
[vprjp](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vprjp_c.html)  
[vprjpi](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vprjpi_c.html)  
[vproj](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vproj_c.html)  
[vrel](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vrel_c.html)  
[vrotv](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vrotv_c.html)  
[vscl](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vscl_c.html)  
[vsep](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vsep_c.html)  
[vsub](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vsub_c.html)  
[vtmv](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vtmv_c.html)  
[vupack](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vupack_c.html)  
[vzero](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vzero_c.html)  
[xpose](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/xpose_c.html)  

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

Euler Angles  
```js
{
    "angle3": angle3,
    "angle2": angle2,
    "angle1": angle1,
    "axis3":  axis3,
    "axis2":  axis2,
    "axis1":  axis1
}
```

Functions will throw an error when they are unable to decipher input.  The error thrown will explain the expected type for the first incorrect argument detected.
In some places inputs can be provided in multiple formats but outputs formats for a given type are intended to remain consistent.  For example `spice.recazl` will *accept* `([x,y,z])`, `("x":x, "y":y, "z":z)`, or `(x, y, z)` while `spice.azlrec` will only *output* `[x,y,z]`.


# Functions

## `axisar` Function Documentation

### Functionality
The `axisar` function constructs a rotation matrix for rotating vectors by a specified angle about a specified axis.

### Usage Examples

**Array Axis:**
```javascript
let axis = [0, 0, 1];
let angle = 3.1415926536; // Angle in radians
let rotationMatrix = spice.axisar(axis, angle);
```

**Object Axis:**
```javascript
axis = {x: 0, y: 0, z: 1};
rotationMatrix = spice.axisar(axis, angle);
```

**Separate Axis Arguments:**
```javascript
rotationMatrix = spice.axisar(0, 0, 1, angle);
```

### Parameters
- `axis`: The axis of rotation. Can be provided as an array `[x, y, z]`, an object `{x:, y:, z:}`, or as separate `x, y, z` arguments.
- `angle`: The rotation angle in radians.

### Return Value
Returns a 3x3 rotation matrix (2D array) representing the rotation.

### Error Handling
- Throws an error if encountered.

### Notes
- This function wraps the NAIF SPICE `axisar_c` function.
- Be aware of the precision limits due to floating-point arithmetic.

## `azlrec` Function Documentation

### Functionality
The `azlrec` function converts from the range, azimuth, and elevation of a point to rectangular coordinates.

### Usage Examples

**Standard Coordinates:**
```javascript
const pi = 3.1415926536;
const rpd = pi / 180;
const azl = {"range": 1.732, "az": 315 * rpd, "el": -35.264 * rpd};

const rec = spice.azlrec(azl, false, false);

const x = rec[0];
const y = rec[1];
const z = rec[2];
```

**Azimuth Counter-Clockwise, Elevation Positive-Z:**
```javascript
const rec = spice.azlrec(azl, true, true);
```

### Parameters
- `azl`: An object containing `range`, `az` (azimuth), and `el` (elevation) properties.
- `azccw`: A boolean flag indicating if azimuth is counter-clockwise (true) or clockwise (false).
- `elplsz`: A boolean flag indicating if elevation is positive towards +Z (true) or towards -Z (false).

### Return Value
Returns an array of rectangular coordinates corresponding to the input azimuthal coordinates.

### Error Handling
- Throws an error if incorrect arguments are provided.

## `b1900` Function Documentation

### Functionality
The `b1900` function returns the Julian Date corresponding to Besselian Date 1900.0.

### Usage Example
```javascript
const b1900 = spice.b1900();
```

### Return Value
Returns the Julian Date corresponding to Besselian Date 1900.0 as a double.

### Notes
- This function wraps the NAIF SPICE `b1900_c` function.
- No input parameters are required.
- Does not throw an error.

## `b1950` Function Documentation

### Functionality
The `b1950` function returns the Julian Date corresponding to Besselian Date 1950.0.

### Usage Example
```javascript
const b1950 = spice.b1950();
```

### Return Value
Returns the Julian Date corresponding to Besselian Date 1950.0 as a double.

### Notes
- This function wraps the NAIF SPICE `b1950_c` function.
- No input parameters are required.
- Does not throw an error.

## `bodvrd` Function Documentation

### Functionality
The `bodvrd` function fetches from the kernel pool the double precision values of an item associated with a body, such as radii or axis lengths.

### Usage Examples

**Fetching Earth Radii:**
```javascript
const earth_radii = spice.bodvrd("EARTH", "RADII");
// earth_radii is a 3D numeric array.
```

**Fetching Radii with Body ID:**
```javascript
const earth_radii = spice.bodvrd("399", "RADII");
// earth_radii is a 3D numeric array.
```

**Fetching 1-Dimensional Value:**
```javascript
const earth_long_axis = spice.bodvrd("EARTH", "LONG_AXIS");
// earth_long_axis is a double-precision number.
```

### Parameters
- `bodynm`: Name of the celestial body (e.g., "EARTH") or body ID (e.g., "399").
- `item`: The item for which values are requested (e.g., "RADII", "LONG_AXIS").
- `maxn` (optional): Maximum number of values expected.

### Return Value
Returns an array of double precision values if the result is multi-dimensional, or a single numeric value if the result is 1-dimensional.

### Error Handling
- Throws an error if incorrect arguments are provided or if the kernel variable is not found.


## `clight` Function Documentation

### Functionality
The `clight` function returns the speed of light in a vacuum, expressed in kilometers per second.

### Usage Example
```javascript
const c = spice.clight();
```

### Return Value
Returns the speed of light in vacuum (km/sec) as a double.

### Notes
- This function wraps the NAIF SPICE `clight_c` function.
- No input parameters are required.
- Does not throw an error.


## `conics` Function Documentation

### Functionality
The `conics` function determines the state (position and velocity) of an orbiting body from a set of orbital elements (elliptic, hyperbolic, or parabolic).

### Usage Example
```javascript
const oscelts = {
    "rp": 1e8,
    "ecc": 0,
    "inc": 1.5707963267948966,
    "lnode": 1.5707963267948966,
    "argp": 0,
    "m0": 0.7853981633974484,
    "t0": 0,
    "mu": 398600.435436096
};
const et = 0;

let state_at_et = spice.conics(oscelts, et);

// position as an [x, y, z] array
let r = state_at_et.r;

// velocity as a [dx, dy, dz] array
let v = state_at_et.v;
```

### Parameters
- `oscelts`: An object containing orbital elements (rp, ecc, inc, lnode, argp, m0, t0, mu).
- `et`: The ephemeris time at which the state of the body is to be computed.

### Return Value
Returns an object containing the state (position 'r' and velocity 'v') of the body.

### Error Handling
- Throws an error if incorrect arguments are provided.


## `convrt` Function Documentation

### Functionality
The `convrt` function converts a numerical value from one unit to another (e.g., miles to kilometers, parsecs to lightyears).

### Usage Examples

**Miles to Kilometers:**
```javascript
const statute_miles = 300.0;
const km = spice.convrt(distsm, "statute_miles", "km");
```

**Parsecs to Lightyears:**
```javascript
const parsecs = 1.0;
const lightyears = spice.convrt(onpars, "PARSECS", "LIGHTYEARS");
```

### Parameters
- `x`: The numeric value to be converted.
- `in`: The unit of the input value (e.g., "statute_miles", "PARSECS").
- `out`: The unit for the output value (e.g., "km", "LIGHTYEARS").

From NAIF SPICE Documentation, the following are recognized units:  
* Angles:
  * "RADIANS"
  * "DEGREES"
  * "ARCMINUTES"
  * "ARCSECONDS"
  * "HOURANGLE"
  * "MINUTEANGLE"
  * "SECONDANGLE"

* Metric Distances:
  * "METERS"
  * "M"
  * "KILOMETERS"
  * "KM"
  * "CENTIMETERS"
  * "CM"
  * "MILLIMETERS"
  * "MM"

* English Distances:
  * "FEET"
  * "INCHES"
  * "YARDS"
  * "STATUTE_MILES"
  * "NAUTICAL_MILES"

* Astrometric Distances:
  * "AU"
  * "PARSECS"
  * "LIGHTSECS"
  * "LIGHTYEARS" julian lightyears

* Time:
  * "SECONDS"
  * "MINUTES"
  * "HOURS"
  * "DAYS"
  * "JULIAN_YEARS"
  * "TROPICAL_YEARS"
  * "YEARS" (same as julian years)

### Return Value
Returns the converted value as a double.

### Error Handling
- Throws an error if conversion between the specified units is not possible or if units are unrecognized.


## `cylrec` Function Documentation

### Functionality
The `cylrec` function converts coordinates from cylindrical to rectangular representation.

### Usage Example
```javascript
const pi = 3.1415926536;
const rpd = pi / 180;
const cyl = {"r": 1.4142, "clon": 45.0 * rpd, "z": 1.0};

// get rectangular coordinates as [x, y, z] array
const rec = spice.cylrec(cyl);
```

### Parameters
- `cyl`: An object representing cylindrical coordinates with properties `r` (radius), `clon` (longitude in radians), and `z` (height).

### Return Value
Returns an array representing the rectangular coordinates corresponding to the input cylindrical coordinates.

### Error Handling
- Throws an error if incorrect arguments are provided.


## `deltet` Function Documentation

### Functionality
The `deltet` function computes the value of Delta ET (ET - UTC) for a given epoch. This function is typically used to convert between Ephemeris Time (ET) and Coordinated Universal Time (UTC).

### Usage Example
```javascript
const epoch = 0;
const eptype = 'UTC';
const delta = spice.deltet(epoch, eptype);
```

### Parameters
- `epoch`: The epoch at which Delta ET is to be computed.
- `eptype`: The type of the input epoch, typically 'UTC'.

### Return Value
Returns the value of Delta ET (ET - UTC) as a double.

### Error Handling
- Throws an error if incorrect arguments are provided.

## `dpr` Function Documentation

### Functionality
The `dpr` function returns the number of degrees per radian, useful for converting angles from radians to degrees.

### Usage Example
```javascript
const degreesPerRadian = spice.dpr();
```

### Return Value
Returns the number of degrees per radian as a double.

### Notes
- This function wraps the NAIF SPICE `dpr_c` function.
- No input parameters are required.
- Does not throw an error.

## `erract` Function Documentation

### Functionality
The `erract` function retrieves or sets the default error action for handling CSPICE errors.

### Usage Example
```javascript
const initialValue = spice.erract('GET');

spice.erract('SET', "IGNORE");
```

### Parameters
- First argument (string): Specifies the action to be performed ('GET' or 'SET').
- Second argument (string, optional): Specifies the error action to set ('ABORT', 'IGNORE', 'REPORT', 'RETURN', 'DEFAULT'). Only required when the first argument is 'SET'.

### Return Value
When used with 'GET', returns the current error action. When used with 'SET', returns the new error action.

### Error Handling
- Throws an error if incorrect arguments are provided.


## `errdev` Function Documentation

### Functionality
The `errdev` function retrieves or sets the name of the current output device for CSPICE error messages.

### Usage Example
```javascript
const initialValue = spice.errdev('GET');

spice.errdev('SET', "./test/temp/tempfile");
```

### Parameters
- First argument (string): Specifies the action to be performed ('GET' or 'SET').
- Second argument (string, optional): The name of the error output device. Only required when the first argument is 'SET'.  Valid values are "SCREEN", "NULL", or a file path.

### Return Value
When used with 'GET', returns the name of the current error output device. When used with 'SET', returns the new error output device name.

### Error Handling
- Throws an error if incorrect arguments are provided.

## `errprt` Function Documentation

### Functionality
The `errprt` function retrieves or sets the list of error message items to be output when a CSPICE error is detected.

### Usage Example
```javascript
const initialValue = spice.errprt('GET');
spice.errprt('SET', "SHORT, LONG");
```

### Parameters
- First argument (string): Specifies the action to be performed ('GET' or 'SET').
- Second argument (string, optional): The list of error message items to output. Only required when the first argument is 'SET'.  For information on valid values consult the NAIF documentation for errprt_c.

### Return Value
When used with 'GET', returns the current list of error message items. When used with 'SET', returns the new list.

### Error Handling
- Throws an error if incorrect arguments are provided.

## `et2utc` Function Documentation

### Functionality
The `et2utc` function converts an input time from ephemeris seconds past J2000 to Calendar, Day-of-Year, or Julian Date format, UTC.

### Usage Example
```javascript
const et = -527644192.5403653;
const calendarFormatted = spice.et2utc(et, "C", 3);
```

### Parameters
- `et`: The ephemeris time in seconds past J2000 to be converted.
- `format`: The format of the output time string ("C" for Calendar, "D" for Day-of-Year, "J" for Julian Date).
- `prec`: The precision of fractional seconds in the output time string.

### Return Value
Returns the converted time as a string in the specified format.

### Error Handling
- Throws an error if incorrect arguments are provided.

## `etcal` Function Documentation

### Functionality
The `etcal` function converts an ephemeris epoch, measured in seconds past the epoch of J2000, to a calendar string.

### Usage Example
```javascript
const et = 0;
const calendarString = spice.etcal(et);
```

### Parameters
- `et`: The ephemeris time in seconds past J2000 to be converted.

### Return Value
Returns a calendar string corresponding to the input ephemeris time.

### Error Handling
- Throws an error if incorrect arguments are provided.


## `eul2m` Function Documentation

### Functionality
The `eul2m` function constructs a rotation matrix from a set of Euler angles.

### Usage Example
```javascript
let pi = spice.pi();
const angle3 = 0;
const angle2 = 0;
const angle1 = pi / 2;
const axis3 = 1;
const axis2 = 2;
const axis1 = 3;

const eulers = {
    angle3, angle2, angle1,
    axis3,  axis2,  axis1
};

const rotationMatrix = spice.eul2m(eulers);
```

### Parameters
- An object with the following required key/value pairs:
- `angle3`, `angle2`, `angle1`: The three Euler angles (in radians).
- `axis3`, `axis2`, `axis1`: The axes of the rotations (1-3)

### Return Value
Returns a 3x3 rotation matrix constructed from the specified Euler angles.

### Error Handling
- Throws an error if incorrect arguments are provided.


## `evsgp4` Function Documentation

### Functionality
The `evsgp4` function evaluates NORAD two-line element data for Earth-orbiting spacecraft, computing position and velocity of the spacecraft at a specified ephemeris time.

### Usage Example
```javascript
const { spice, getGeophysicalConstants } = require('js-spice');

const geophs = await getGeophysicalConstants(true, 'pck/geophysical.ker', 'kennel_cache/naif/generic_kernels');

const et = spice.str2et('2020-05-26 02:25:00');
const tle = [
    '1 43908U 18111AJ  20146.60805006  .00000806  00000-0  34965-4 0  9999',
    '2 43908  97.2676  47.2136 0020001 220.6050 139.3698 15.24999521 78544'
];
const { elems } = spice.getelm(1957, tle);

const state = spice.evsgp4(et, geophs, elems);

// where is it a day later?
// r = [x, y, z] array
// v = [dx, dy, dz] array
const {r, v} = spice.evsgp4(et + spice.spd(), geophs, elems);
```

### Parameters
- `et`: The ephemeris time at which the state is to be computed.
- `geophs`: An array of geophysical constants.  see
- `elems`: An array of elements from the NORAD two-line elements.

### Return Value
Returns an object containing the state (position 'r' and velocity 'v') of the spacecraft.

### Error Handling
- Throws an error if incorrect arguments are provided.


## `failed` Function Documentation

### Functionality
The `failed` function checks if an error is currently signaled in the CSPICE system.  Note that js-spice wrapped functions, reset the error status before throwing an exception.

### Usage Examples

**Check for No Error:**
```javascript
spice.reset();
const failed = spice.failed();
// failed will be false
```

**Check for Signaled Error:**
```javascript
spice.sigerr('Houston, we have a problem.');
const failed = spice.failed();
// failed will be true

spice.reset(/*Failure is not an option*/);
```

### Return Value
Returns a boolean value: `true` if an error is currently signaled, `false` otherwise.

### Notes
- This function wraps the NAIF SPICE `failed_c` function.
- No input parameters are required.
- Does not throw an error.


## `furnsh` Function Documentation

### Functionality
The `furnsh` function furnishes a program with SPICE kernels. It is used to load one or more SPICE kernel files into a program.

### Usage Examples

**Load a Single Kernel File:**
```javascript
const singleFilePathStr = './test/data/naif/generic_kernels/pck00009.tpc';
spice.furnsh(singleFilePathStr);
```

**Load Multiple Kernel Files:**
```javascript
const pathsArray = ['./path/to/kernel1', './path/to/kernel2'];
spice.furnsh(pathsArray);
```

**Error Handling Example:**
```javascript
spice.furnsh("badpath");
// the next line will never execute (unless you have a kernel named 'badpath', but you don't.)
```

### Parameters
- Can be a single string specifying the path to a kernel file, or an array of strings specifying multiple paths.

### Return Value
Does not return a value. Kernels are loaded into the program's internal data space.

### Error Handling
- Throws an error if a kernel file cannot be found or if the input is not a string or an array of strings.


## `georec` Function Documentation

### Functionality
The `georec` function converts geodetic coordinates (longitude, latitude, altitude) to rectangular coordinates.

### Usage Example
```javascript
const radius = 6378.2064;
const f = 1. / 294.9787;
const pi = 3.1415926536;
const rpd = pi / 180;
const geo = {"lon": 90.0 * rpd, "lat": 0, "alt": 0};

// get rectancular coordinates as [x, y, z] array
const rec = spice.georec(geo, radius, f);
```

### Parameters
- `lon`, `lat`, `alt`: Longitude, latitude, and altitude in the geodetic coordinate system.
- `re`: The equatorial radius of the reference spheroid in kilometers.
- `f`: The flattening coefficient of the reference spheroid.

### Return Value
Returns an array representing the rectangular coordinates corresponding to the input geodetic coordinates.

### Error Handling
- Throws an error if incorrect arguments are provided.

## `getelm` Function Documentation

### Functionality
The `getelm` function evaluates NORAD two-line element data for Earth-orbiting spacecraft, extracting orbital elements from the two-line element set.

### Usage Example
```javascript
const tle = [
    '1 43908U 18111AJ  20146.60805006  .00000806  00000-0  34965-4 0  9999',
    '2 43908  97.2676  47.2136 0020001 220.6050 139.3698 15.24999521 78544'
];
const {elems} = spice.getelm(1957, tle);
```

### Parameters
- `frstyr`: The first two digits of the year corresponding to the earliest representable two-line elements.
- `tle`: An array containing the two lines of NORAD two-line element data as strings.

### Return Value
Returns an object containing 'elems', the extracted orbital elements and the epoch of the elements and 'epoch'.  This is of the form:

```javascript
{
    elems: 
    {
        "ndt20": 2.4422489185892878e-11,
        "ndd60": 0,
        "bstar": 0.000034965,
        "incl":  1.6976398755128366,
        "node0": 0.8240327717195948,
        "ecc":   0.0020001,
        "omega": 3.8502835963620905,
        "m0":    2.432461887845993,
        "n0":    0.06654065683196603,
        "epoch": 643689404.7102276
    },
    epoch: 643689404.7102276
}
```

### Error Handling
- Throws an error if incorrect arguments are provided.

## `gfposc` Function Documentation

### Functionality
The `gfposc` function determines time intervals for which a coordinate of an observer-target position vector satisfies a numerical constraint, typically used for visibility or occultation events.

### Usage Example
```javascript
const et0 = spice.str2et("2009 JAN 1");
const et1 = spice.str2et("2009 JAN 5");
const cnfine = [[et0, et1]];
const obsrvr = "DSS-14";
const target = "SATURN";
const frame  = "DSS-14_TOPO";
const crdsys = "LATITUDINAL";
const coord  = "LATITUDE";
const relate = ">";
const refval = 6.0 * spice.rpd();
const abcorr = "LT+S";
const step   = spice.spd() / 4;
const adjust = 0.0;

// Get the intervals as an array of et pairs [[start1, end1], [start2, end2], ...]
const timeWindows = spice.gfposc(target, frame, abcorr, obsrvr, crdsys, coord, relate, refval, adjust, step, cnfine);
```

### Parameters
- `target`, `frame`, `abcorr`, `obsrvr`: Target, frame, aberration correction, and observer names.
- `crdsys`, `coord`: Coordinate system and coordinate name.
- `relate`: Relational operator ('<', '>', '=', '>=', '<=', '!=').
- `refval`: Reference value for the constraint.
- `adjust`: Adjustment value for absolute extremal searches.
- `step`: Step size in seconds for the search.
- `cnfine`: Confinement window for the search.

### Return Value
Returns an array of time windows (et [start, end] arrays) when the specified constraint is satisfied.

### Error Handling
- Throws an error if incorrect arguments are provided.

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

## `gfsep` Function Documentation

### Functionality
The `gfsep` function determines time intervals when the angular separation between the position vectors of two target bodies relative to an observer satisfies a numerical relationship. It is commonly used to find events like conjunctions and oppositions.

### Usage Example
```javascript
const targ1 = "MOON";
const shape1 = "SPHERE";
const frame1 = "NULL";
const targ2 = "EARTH";
const shape2 = "SPHERE";
const frame2 = "NULL";
const abcorr = "NONE";
const obsrvr = "SUN";
const relate = "LOCMAX";
const step   = 6. * spice.spd();
const adjust = 0;
const refval = 0;

const et1 = spice.str2et("2007 JAN 01");
const et2 = spice.str2et("2007 JUL 01");
const cnfine = [[et1, et2]];

// Get the intervals as an array of et pairs [[start1, end1], [start2, end2], ...]
const timeWindows = spice.gfsep(
    targ1, shape1, frame1, targ2, shape2, frame2, abcorr, obsrvr, relate, refval, adjust, step, cnfine);
```

### Parameters
- `targ1`, `shape1`, `frame1`: The first target, its shape, and frame.
- `targ2`, `shape2`, `frame2`: The second target, its shape, and frame.
- `abcorr`, `obsrvr`: Aberration correction and the observer's name.
- `relate`: The relational condition for the search ('=', '!=', '<', '>', '<=', '>=', 'LOCMAX', 'LOCMIN', 'ABSMAX', 'ABSMIN').
- `refval`, `adjust`, `step`: Reference value, adjustment value for absolute extremal searches, and the search step size.
- `cnfine`: The confinement window for the search.

### Return Value
Returns an array of time windows when the specified condition is satisfied.

### Error Handling
- Throws an error if incorrect arguments are provided.


## `halfpi` Function Documentation

### Functionality
The `halfpi` function returns half the value of π (pi). This function is useful in calculations involving radians and degrees, especially in trigonometric functions.

### Usage Example
```javascript
const halfpi = spice.halfpi();
```

### Return Value
Returns half the value of π as a double.

### Notes
- This function wraps the NAIF SPICE `halfpi_c` function.
- No input parameters are required.
- Does not throw an error.

## `ident` Function Documentation

### Functionality
The `ident` function returns the 3x3 identity matrix. This matrix is often used in linear algebra and transformations involving coordinates and rotations.

### Usage Example
```javascript
// load the identy matrix as [[1, 0, 0], [0, 1, 0], [0, 0, 1]]
const m_identity = spice.ident();
```

### Return Value
Returns the 3x3 identity matrix.

### Notes
- This function wraps the NAIF SPICE `ident_c` function.
- No input parameters are required.
- Does not throw an error.

## `invert` Function Documentation

### Functionality
The `invert` function generates the inverse of a 3x3 matrix. This function is commonly used in linear algebra, especially in transformations and rotations.

### Usage Example
```javascript
const m = [[0, -1, 0], [0.5, 0, 0], [0, 0, 1]];
const inverse = spice.invert(m);
```

### Parameters
- `m`: The 3x3 matrix to be inverted.

### Return Value
Returns the inverse of the given 3x3 matrix.

### Error Handling
- Throws an error if incorrect arguments are provided.

## `j1900` Function Documentation

### Functionality
The `j1900` function returns the Julian Date corresponding to the date 1899 DEC 31 12:00:00 (1900 JAN 0.5). This is often used as a standard reference date in astronomical calculations.

### Usage Example
```javascript
const j1900 = spice.j1900();
```

### Return Value
Returns the Julian Date of 1899 DEC 31 12:00:00 as a double.

### Notes
- This function wraps the NAIF SPICE `j1900_c` function.
- No input parameters are required.
- Does not throw an error.

## `j1950` Function Documentation

### Functionality
The `j1950` function returns the Julian Date corresponding to the date 1950 JAN 01 00:00:00 (1950 JAN 1.0). This date is often used as a standard epoch in astronomical calculations.

### Usage Example
```javascript
const actual = spice.j1950();
```

### Return Value
Returns the Julian Date of 1950 JAN 01 00:00:00 as a double.

### Notes
- This function wraps the NAIF SPICE `j1950_c` function.
- No input parameters are required.
- Does not throw an error.

## `j2000` Function Documentation

### Functionality
The `j2000` function returns the Julian Date corresponding to the date 2000 JAN 01 12:00:00 (2000 JAN 1.5). This is a key reference date in astronomical and space mission calculations.

### Usage Example
```javascript
const j2000 = spice.j2000();
```

### Return Value
Returns the Julian Date of 2000 JAN 01 12:00:00 as a double.

### Notes
- This function wraps the NAIF SPICE `j2000_c` function.
- No input parameters are required.
- Does not throw an error.

## `j2100` Function Documentation

### Functionality
The `j2100` function returns the Julian Date corresponding to the date 2100 JAN 01 12:00:00 (2100 JAN 1.5). This date is often used in long-term astronomical and space mission calculations.

### Usage Example
```javascript
const j2100 = spice.j2100();
```

### Return Value
Returns the Julian Date of 2100 JAN 01 12:00:00 as a double.

### Notes
- This function wraps the NAIF SPICE `j2100_c` function.
- No input parameters are required.
- Does not throw an error.

## `jyear` Function Documentation

### Functionality
The `jyear` function returns the number of seconds in a Julian year. This is a key constant in time system conversions and astronomical calculations.

### Usage Example
```javascript
const jyear = spice.jyear();
```

### Return Value
Returns the number of seconds in a Julian year as a double.

### Notes
- This function wraps the NAIF SPICE `jyear_c` function.
- No input parameters are required.
- Does not throw an error.

## `kclear` Function Documentation

### Functionality
The `kclear` function clears all loaded SPICE kernels from the program's internal data space. It is often used in unit testing and when resetting the kernel pool is necessary.

### Usage Example
```javascript
spice.kclear();
```

### Notes
- This function wraps the NAIF SPICE `kclear_c` function.
- No input parameters are required.
- Does not throw an error.


## `latrec` Function Documentation

### Functionality
The `latrec` function converts from latitudinal coordinates (radius, longitude, latitude) to rectangular coordinates.

### Usage Example
```javascript
const lat = {"radius": 403626.33912495, "lon": -98.34959789 * spice.rpd(), "lat": -18.26566077 * spice.rpd()};
const rec = spice.latrec(lat);

const x = rec[0];
const y = rec[1];
const z = rec[2];
```

### Parameters
- `radius`: The distance of the point from the origin.
- `lon`: The longitude of the point in radians.
- `lat`: The latitude of the point in radians.

### Return Value
Returns an array representing the rectangular coordinates corresponding to the input latitudinal coordinates.

### Error Handling
- Throws an error if incorrect arguments are provided.

## `m2eul` Function Documentation

### Functionality
The `m2eul` function factors a rotation matrix as a product of three rotations about specified coordinate axes.

### Usage Example
```javascript
const r = [[0, 1, 0], [-1, 0, 0], [0, 0, 1]];
const axis3 = 1;
const axis2 = 2;
const axis1 = 3;

const eulers = spice.m2eul(r, axis3, axis2, axis1);
```

### Parameters
- `r`: The rotation matrix to be factored.
- `axis3`, `axis2`, `axis1`: The axes of the rotations.

### Return Value
Returns an object containing the Euler angles and axes associated with the factored rotation.
- An object with the following key/value pairs:
- `angle3`, `angle2`, `angle1`: The three Euler angles (in radians).
- `axis3`, `axis2`, `axis1`: The axes of the rotations (1-3)

### Error Handling
- Throws an error if incorrect arguments are provided.

## `m2q` Function Documentation

### Functionality
The `m2q` function finds a unit quaternion corresponding to a specified rotation matrix. Quaternions are used in rotations and orientation calculations in three-dimensional space.

### Usage Example
```javascript
let pi = 3.1415926536;
const r = spice.rotate(pi/2, 3);
const quat = spice.m2q(r);

const qx = quat.x;
const qy = quat.y;
const qz = quat.z;
const qw = quat.w;
```

### Parameters
- `r`: The rotation matrix to be converted into a quaternion.

### Return Value
Returns a unit quaternion corresponding to the given rotation matrix.

### Error Handling
- Throws an error if incorrect arguments are provided.


## `mtxm` Function Documentation

### Functionality
The `mtxm` function multiplies the transpose of the first input matrix with the second input matrix. This operation is commonly used in linear algebra, particularly in transformations and rotations.

### Usage Example
```javascript
let m1 = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]; // This matrix will be transposed
let m2 = [[1, 0, 0], [0, 1, 0], [0, 0, 1]]; // This matrix remains as is
let m1t_x_m2 = spice.mtxm(m1, m2); // Multiplication after transposing m1
```

### Parameters
- `m1`: The first 3x3 matrix to be transposed and then multiplied.
- `m2`: The second 3x3 matrix.

### Return Value
Returns the product of the transposed first matrix and the second matrix as a 3x3 matrix.

### Error Handling
- Throws an error if incorrect arguments are provided.

## `mtxv` Function Documentation

### Functionality
The `mtxv` function multiplies the transpose of a 3x3 matrix with a 3-dimensional vector. This operation is commonly used in coordinate transformations and vector rotations.

### Usage Example
```javascript
let m = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]; // The matrix to be transposed
let v = [1, 0, 0]; // The vector

let mt_x_v = spice.mtxv(m, v); // Multiplication after transposing m

const x = mt_x_v[0];
const y = mt_x_v[1];
const z = mt_x_v[2];
```

### Parameters
- `m`: The 3x3 matrix to be transposed.
- `v`: The 3-dimensional vector.

### Return Value
Returns the product of the transposed matrix and the vector as a 3-dimensional vector.

### Error Handling
- Throws an error if incorrect arguments are provided.

## `mxm` Function Documentation

### Functionality
The `mxm` function multiplies two 3x3 matrices. This operation is widely used in linear algebra, particularly in transformations and rotations.

### Usage Example
```javascript
let m1 = [[1, 2, 3], [4, 5, 6], [7, 8, 9]];
let m2 = [[1, 0, 0], [0, 1, 0], [0, 0, 1]];

// the result will be in the same form as m1, m2 above
let m_x_m = spice.mxm(m1, m2);
```

### Parameters
- `m1`, `m2`: The two 3x3 matrices to be multiplied.

### Return Value
Returns the product of the two matrices as a 3x3 matrix.

### Error Handling
- Throws an error if incorrect arguments are provided.


## `mxmt` Function Documentation

### Functionality
The `mxmt` function multiplies the first 3x3 matrix with the transpose of the second 3x3 matrix. This operation is used in linear algebra, particularly in coordinate transformations and rotations.

### Usage Example
```javascript
let m1 = [[1, 0, 0], [0, 1, 0], [0, 0, 1]]; // First matrix
let m2 = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]; // Second matrix, to be transposed
let m_x_mt = spice.mxmt(m1, m2); // Multiplication with transpose of m2
```

### Parameters
- `m1`: The first 3x3 matrix.
- `m2`: The second 3x3 matrix, which will be transposed.

### Return Value
Returns the product of the first matrix and the transpose of the second matrix as a 3x3 matrix.

### Error Handling
- Throws an error if incorrect arguments are provided.

## `mxv` Function Documentation

### Functionality
The `mxv` function multiplies a 3x3 matrix with a 3-dimensional vector. This operation is commonly used in coordinate transformations and vector rotations.

### Usage Example
```javascript
let m = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]; // The matrix
let v = [1, 0, 0]; // The vector

let m_x_v = spice.mxv(m, v); // Multiplication of matrix and vector

// result was [x, y, z] array
const x = m_x_v[0];
const y = m_x_v[1];
const z = m_x_v[2];
```

### Parameters
- `m`: The 3x3 matrix.
- `v`: The 3-dimensional vector.

### Return Value
Returns the product of the matrix and the vector as a 3-dimensional vector.

### Error Handling
- Throws an error if incorrect arguments are provided.

## `nvc2pl` Function Documentation

### Functionality
The `nvc2pl` function creates a SPICE plane from a specified normal vector and a constant. This is often used in geometric computations involving planes.

### Usage Example
```javascript
const normal = [1, 2, 3];
const constant = 4;

// plane will be of the form { "normal": [1, 2, 3], "constant": 4}
// and ready to be passed into functions such as vprjp.
const plane = spice.nvc2pl(normal, constant);
```

### Parameters
- `normal`: A 3-dimensional normal vector.
- `konst`: A scalar constant.

### Return Value
Returns a SPICE plane defined by the normal vector and the constant.

### Error Handling
- Throws an error if incorrect arguments are provided.

## `nvp2pl` Function Documentation

### Functionality
The `nvp2pl` function creates a SPICE plane from a specified normal vector and a point. This function is useful in geometric computations involving planes.

### Usage Example
```javascript
const normal = [1, 2, 3];
const point = [1, 2, 3];

// plane will be of the form { "normal": [1, 2, 3], "constant": 4}
// and ready to be passed into functions such as vprjp.
const plane = spice.nvp2pl(normal, point);
```

### Parameters
- `normal`: A 3-dimensional normal vector.
- `point`: A 3-dimensional point vector.

### Return Value
Returns a SPICE plane defined by the normal vector and the point.

### Error Handling
- Throws an error if incorrect arguments are provided.


## `oscelt` Function Documentation

### Functionality
The `oscelt` function computes the set of osculating conic orbital elements corresponding to the state (position and velocity) of a body. This is essential in celestial mechanics and orbital calculations.

### Usage Example
```javascript
const mu = 3.9860043543609598e5;
const r = 1e8;
const speed = Math.sqrt(mu/r);
const pvinit = {
    "r": [0, r/Math.sqrt(2), r/Math.sqrt(2)],
    "v": [0, -speed/Math.sqrt(2), speed/Math.sqrt(2)]
};
const et = 0;

const elts = spice.oscelt(pvinit, et, mu);
```

### Parameters
- `state`: The state vector (position and velocity) of the body.
- `et`: The ephemeris time.
- `mu`: The gravitational parameter (GM) of the primary body.

### Return Value
Returns the set of osculating conic orbital elements as an object of the form:
```javascript
{
    "rp": 1e8,
    "ecc": 0,
    "inc": 1.5707963267948966,
    "lnode": 1.5707963267948966,
    "argp": 0,
    "m0": 0.7853981633974484,
    "t0": 0,
    "mu": 398600.435436096
};
```

### Error Handling
- Throws an error if incorrect arguments are provided.

## `pckfrm` Function Documentation

### Functionality
The `pckfrm` function retrieves the set of reference frame class ID codes from all frames in a specified binary PCK (Planetary Constants Kernel) file. This is useful in planetary science and navigation.

### Usage Example
```javascript
const singleFilePathStr = 'path/to/pck/file.bpc';
const idCodeArray = spice.pckfrm(singleFilePathStr);
```

### Parameters
- `pckfnm`: File path to the binary PCK file.

### Return Value
Returns an array of reference frame class ID codes found in the specified PCK file.

### Error Handling
- Throws an error if incorrect arguments are provided or if the file cannot be accessed.

## `pgrrec` Function Documentation

### Functionality
The `pgrrec` function converts planetographic coordinates to rectangular coordinates. It's essential for working with planetary data in different coordinate systems.

### Usage Example
```javascript
const { spice, getKernels } = require('js-spice');
await getKernels('pck/a_old_versions/pck00008.tpc', 'kernel_cache/data/naif/generic_kernels');
const re = 3396.190;
const rp = 3376.200;
const f = (re - rp) / re;
const pgr = {"lon": 270.000 * spice.rpd(), "lat": 0, "alt": 0};
const rec = spice.pgrrec('mars', pgr, re, f);

// rec will be an array of the form [x, y, z]
```

### Parameters
- `body`: Name of the body.
- `lon`, `lat`, `alt`: Longitude, latitude, and altitude.
- `re`: Equatorial radius of the reference spheroid in kilometers.
- `f`: Flattening coefficient.

### Return Value
Returns rectangular coordinates based on the given planetographic coordinates.

### Error Handling
- Throws an error if incorrect arguments are provided or if the specified body is not recognized.

## `pi` Function Documentation

### Functionality
The `pi` function returns the mathematical constant π (pi), the ratio of a circle's circumference to its diameter.

### Usage Example
```javascript
const actual = spice.pi(); // Returns the value of pi
```

### Parameters
This function does not require any parameters.

### Return Value
Returns the (delicious) value of π (pi).  

[editor's note: please remove 'delicious', astrophysics has no space for humor.]  
[author's note: No problem, I'll take care of it tomorrow.]

### Error Handling
- Throws an error if any arguments are provided.

## `pl2nvc` Function Documentation

### Functionality
The `pl2nvc` function computes a unit normal vector and constant that define a specified plane. This is particularly useful in computational geometry involving planes.

### Usage Example
```javascript
const plane = { normal: [1, 2, 3], constant: 4 };
const {normal, constant} = spice.pl2nvc(plane);
```

### Parameters
- `plane`: The plane object defined by its normal vector and a constant representing a SPICE plane.

### Return Value
Returns an object with the normalized vector and adjusted constant of the plane.

### Error Handling
- Throws an error if incorrect arguments are provided.

## `pl2nvp` Function Documentation

### Functionality
The `pl2nvp` function computes a unit normal vector and a point that define a specified plane. This is valuable in spatial geometry and computational mathematics.

### Usage Example
```javascript
const plane = { normal: [1, 2, 3], constant: 4 };
const {normal, point} = spice.pl2nvp(plane);
```

### Parameters
- `plane`: A plane object defined by a normal vector and a constant of a SPICE plane.

### Return Value
Returns an object with a normalized vector and a point that represent the plane.

### Error Handling
- Throws an error if incorrect arguments are provided or if the plane cannot be properly defined.


## `pl2psv` Function Documentation

### Functionality
The `pl2psv` function computes a point and two orthogonal spanning vectors that generate a specified plane. This function is essential in computational geometry to represent planes in three-dimensional space.

### Usage Example
```javascript
const plane = { normal: [1, 2, 3], constant: 4 };
const {point, span1, span2} = spice.pl2psv(plane);
```

### Parameters
- `plane`: A plane object defined by a normal vector and a constant.

### Return Value
Returns an object with a point and two spanning vectors representing the plane ('point', 'span1', and 'span2' key/value pairs).

### Error Handling
- Throws an error if incorrect arguments are provided or if the plane cannot be properly represented.



## `prop2b` Function Documentation

### Functionality
The `prop2b` function computes the state (position and velocity) of a massless body at a specified time, using a two-body force model. This is useful for calculating orbits around a central mass.

### Usage Examples
```javascript
const gm = 398600.435436096;
const state = {"r": [7000, 0, 0], "v": [0, 7.546049108166282, 0]};
const dt = 3600;

let {r, v} = spice.prop2b(gm, state, dt);
```

### Parameters
- `gm`: Gravitational constant times the mass of the central body.
- `state`: Initial state of the body, containing `r` (position vector) and `v` (velocity vector).
- `dt`: Time increment at which the new state is computed.

### Return Value
Returns the new state of the body after time `dt`, containing `r` (position) and `v` (velocity) vectors.

### Error Handling
- Throws an error for degenerate orbits or incorrect dimensions/types of input vectors.


## `psv2pl` Function Documentation

### Functionality
The `psv2pl` function creates a SPICE plane from a point and two spanning vectors.

### Usage Example
```javascript
const point = [1, 2, 3];
const span1 = [1, 1, 0];
const span2 = [0, 1, 1];

const plane = spice.psv2pl(point, span1, span2);

// 'plane' will be an object of the form {"normal":[x, y, z], "constant":c}, which is
// the form expected by other js-spice functions.
```

### Parameters
- `point`: A three-element array representing a point on the plane.
- `span1`: A three-element array representing the first spanning vector.
- `span2`: A three-element array representing the second spanning vector.

### Return Value
Returns an object representing the plane, with properties for the normalized normal vector and the plane constant.

### Error Handling
- Throws an error if incorrect arguments are provided.



## `pxform` Function Documentation

### Functionality
The `pxform` function calculates the transformation matrix that converts position vectors from one specified reference frame to another at a given epoch.

### Usage Example
```javascript
const et = 0; // Epoch in ephemeris seconds past J2000
const r = spice.pxform('IAU_EARTH', 'J2000', et);

// r is now a rotation matrix of the form [[a,b,c],[d,e,f],[g,h,i]]
```

### Parameters
- `from`: The name of the frame to transform from.
- `to`: The name of the frame to transform to.
- `et`: The epoch of the transformation in ephemeris seconds past J2000.

### Return Value
Returns a 3x3 transformation matrix.

### Error Handling
- Throws an error if the specified frames are not recognized or the transformation cannot be computed.


## `pxfrm2` Function Documentation

### Functionality
The `pxfrm2` function returns the matrix that transforms position vectors from one specified frame to another at different epochs. This is particularly useful when dealing with frames that are moving with respect to each other.

### Usage Example
```javascript
await getKernels('pck/a_old_versions/pck00009.tpc', 'kernel_cache/data/naif/generic_kernels');
let r = spice.pxfrm2('IAU_EARTH', 'J2000', etfrom, etto);
```

### Parameters
- `from`: The name of the frame to transform from.
- `to`: The name of the frame to transform to.
- `etfrom`: Epoch in ephemeris seconds past J2000 to evaluate the `from` frame.
- `etto`: Epoch in ephemeris seconds past J2000 to evaluate the `to` frame.

### Return Value
Returns a 3x3 matrix representing the rotation from the `from` frame to the `to` frame.

### Error Handling
- Throws an error if incorrect or invalid frame names are provided, or if the epochs are invalid.


## `q2m` Function Documentation

### Functionality
The `q2m` function calculates the rotation matrix corresponding to a specified unit quaternion. It is typically used to convert quaternion representations of rotations into matrix form, which is more suitable for certain types of calculations.

## Usage Example
```javascript
const s = Math.sqrt(2) / 2;
const q = {"x": 0, "y": 0, "z": -s, "w": s};

const m = spice.q2m(q);

// m now contains a 3x3 array of matrix values.
```

### Parameters
- `q`: The input quaternion represented as an object with `x`, `y`, `z`, and `w` components.

### Return Value
Returns a 3x3 rotation matrix corresponding to the given quaternion.

### Error Handling
- Throws an error if the input is not a unit quaternion.
- Handles cases where input quaternion components are not in the expected format.

### Note
This function is essential for converting quaternion representations, commonly used in spacecraft attitude control and 3D graphics, into rotation matrices that can be easily used for further geometric transformations.



## `qxq` Function Documentation

### Functionality
The `qxq` function multiplies two quaternions, `q1` and `q2`. This operation is essential in computational geometry, particularly in spacecraft attitude and orientation calculations.

### Usage Example
```javascript
const q1 = {"x":1, "y":0, "z":0, "w":0};
const q2 = {"x":0, "y":1, "z":0, "w":0};

const q_x_q = spice.qxq(q1, q2);
```

### Parameters
- `q1`: The first quaternion.
- `q2`: The second quaternion.

### Return Value
Returns the product of the two quaternions as a new quaternion.

### Error Handling
- Throws an error if incorrect arguments are provided.


## `recrad`` Function Documentation

### Functionality
`recrad` converts rectangular coordinates to range, right ascension, and declination.

### Usage Example
```cpp
const rec = [0,0.7071067811847432,0.7071067811883519];
const rad = spice.recrad(rec);

// rad is of the form: {"range": 1, "ra":1.5708, "dec":0.785398}
```

### Parameters
- `rec`: An array representing rectangular coordinates.

### Return Value
Returns an object containing the range, right ascension, and declination derived from the input rectangular coordinates.

### Error Handling
This function throws a TypeError if incorrect arguments are provided. It does not throw any SPICE errors.


## `raxisa` Function Documentation

### Functionality
The `raxisa` function computes the axis of the rotation given by an input matrix and the angle of rotation. It is useful for understanding and manipulating rotational transformations.

### Usage Example
```javascript
const m = [[0, 1, 0], [-1, 0, 0], [0, 0, 1]];
const { axis, angle } = spice.raxisa(m);
```

### Parameters
- `matrix`: A 3x3 rotation matrix.

### Return Value
An object containing:
- `axis`: The rotation axis as a 3-element array.
- `angle`: The rotation angle in radians.

### Error Handling
This function validates input types and values, and throws a `TypeError` in case of invalid inputs.  It throws a generic error when the input is not a rotation matrix.


## recazl

### Functionality
The `recazl` function converts rectangular coordinates of a point to range, azimuth, and elevation.

### Usage
```javascript
const rec = [1, 1, 1];
const actual = spice.recazl(rec, false, false);
```

### Parameters
- `rectan`: An array of rectangular coordinates of the point.
- `azccw`: A boolean flag indicating if the azimuth increases in the clockwise direction.
- `elplsz`: A boolean flag indicating if the elevation increases towards the +Z axis.

### Return
Returns an object containing the range, azimuth, and elevation.

### Error Handling
This function throws errors if invalid argument types are provided.



## `reccyl` Function Documentation

### Functionality
The `reccyl` function converts rectangular coordinates to cylindrical coordinates.

### Usage Example
```javascript
const rec = [1, 1, 1];
const cyl = spice.reccyl(rec);

// expected = {"r": 1.4142, "clon":45.0*rpd, "z":1.0};
```

### Parameters
- `rec`: The rectangular coordinates of the point.

### Return Value
Returns an object containing the cylindrical coordinates `r` (radius), `clon` (cylindrical longitude), and `z` (height).

### Error Handling
This function throws a `TypeError` if incorrect arguments are provided. It does not throw a SPICE error.


## `recgeo` Function Documentation

### Functionality
The `recgeo` function converts rectangular coordinates to geodetic coordinates, defined by the equatorial radius and flattening coefficient of a reference spheroid.

### Usage Example
```javascript
const radius = 6378.2064;
const f = 1./294.9787;
const rec = [0.000, 6378.206, 0.000];
const geo = spice.recgeo(rec, radius, f);

// Expected { "lon": 90.0 * rpd, "lat":0, "alt":0 }
```

### Parameters
- `rectan`: Array of rectangular coordinates [X, Y, Z].
- `re`: Equatorial radius of the reference spheroid (in kilometers).
- `f`: Flattening coefficient.

### Return Value
Returns an object containing longitude (`lon`), latitude (`lat`), and altitude (`alt`).

### Error Handling
This function throws an error if incorrect argument types are provided.


## `reclat` Function Documentation

### Functionality
The `reclat` function converts rectangular coordinates to latitudinal coordinates.

### Usage Example
```javascript
const rec = [-55658.44323296, -379226.32931475, -126505.93063865];
const lat = spice.reclat(rec);

// expected = {"radius": 403626.33912495, "lon":-98.34959789*rpd, "lat":-18.26566077*rpd};
```

### Parameters
- `rec`: Array of three elements representing the rectangular coordinates (X, Y, Z).

### Return Value
Returns an object with latitudinal coordinates:
- `radius`: The distance of the point from the origin.
- `lon`: Longitude of the point in radians.
- `lat`: Latitude of the point in radians.

### Error Handling
This function throws a `TypeError` if the input arguments are not as expected.




## `recpgr` Function Documentation

### Functionality
The `recpgr` function converts rectangular coordinates to planetographic coordinates.

### Usage Example
```javascript
await getKernels('pck/a_old_versions/pck00008.tpc');       

const re = 3396.190;
const rp = 3376.200;
const f = (re-rp)/re;

const rec = [0.000, 3396.190, 0.000];
const actual = spice.recpgr('mars', rec, re, f);

// expected = {"lon": 270.000 * rpd, "lat":0, "alt":0};
```

### Parameters
- `body_str`: Name of the central body.
- `rectan`: Rectangular coordinates of a point.
- `re`: Equatorial radius of the reference spheroid in km.
- `f`: Flattening coefficient.

### Return Value
Returns planetographic coordinates (longitude, latitude, altitude) of the input point.

### Error Handling
This function throws an error if invalid arguments are provided.


## `recrad` Function Documentation

### Functionality
The `recrad` function converts rectangular coordinates to spherical coordinates (range, right ascension, and declination).

### Usage Example
```javascript
const rec = [0, 0.7071067811847432, 0.7071067811883519];
const rad = spice.recrad(rec);

// expected = {"range": 1, "ra": 90.0 * rpd, "dec": 45.0 * rpd};
```

### Parameters
- `rectan`: Array of rectangular coordinates.
- `range`: Distance of the point from the origin.
- `ra`: Right ascension of the point.
- `dec`: Declination of the point.

### Return Value
Returns an object containing the spherical coordinates (range, right ascension, and declination).

### Error Handling
This function throws an error if invalid arguments are provided.


## `recsph` Function Documentation

### Functionality
The `recsph` function converts rectangular coordinates to spherical coordinates.

### Usage Example
```javascript
const rec = [0, 0.7071067811847432, 0.7071067811883519];
const sph = spice.recsph(rec);

// expected = {"r": 1, "colat": 45.0 * rpd, "slon": 90.0 * rpd};
```

### Parameters
- `rectan`: Rectangular coordinates of a point.

### Return Value
Returns spherical coordinates (radius, colatitude, and slon) of the input point.

### Error Handling
This function does not throw a SPICE error.


## `reset` Function Documentation

### Functionality
The `reset` function is used primarily for unit testing. It clears any SPICE error.

### Usage Example
```javascript
// Signal an error
spice.sigerr('houston, we have a problem.');

// Failure is not an option
spice.reset();
```

### Error Handling
This function does not throw an error.



## `rotate` Function Documentation

### Functionality
The `rotate` function calculates the 3x3 rotation matrix generated by a rotation of a specified angle about a specified axis.

### Usage Example
```javascript
const r = spice.rotate(3.14159265358979/2, 3);

// expect r = [[0, 1, 0], [-1, 0, 0], [0, 0, 1]];
```

### Parameters
- `angle`: The rotation angle in radians.
- `iaxis`: The axis index about which the rotation is to be performed (1, 2, or 3).

### Return Value
Returns the resulting 3x3 rotation matrix.

### Error Handling
This function throws an error if invalid arguments are provided.

# `rpd` Function Documentation

## Functionality
The `rpd` function returns the number of radians per degree.

## Usage Example
```javascript
const degrees_per_radian = spice.rpd();
```

## Parameters
This function does not require any parameters.

## Return Value
Returns the number of radians per degree.

## Error Handling
This function throws an error if any argument is provided.



## `sigerr` Function Documentation

### Functionality
The `sigerr` function is part of a node-gyp implementation that wraps the NASA/NAIF CSPICE Library. It is used to signal an error in the CSPICE system.

### Usage Example
```javascript
// Signal a SPICE error with a custom message
spice.sigerr('houston, we have a problem.');

// Check if an error has been signaled
const failed = spice.failed();

// we should expect 'failed' to be true now.
spice.reset();

```

### Parameters
- `err`: A string message that describes the error. This message is passed to the CSPICE system.

### Error Handling
- The function will signal an error to the CSPICE system using the provided message.
- No return value is expected as the primary purpose is to signal the error state.

### Source and Test Files
- The implementation of `sigerr` can be found in `sigerr.cpp`, which is part of the node-gyp implementation.
- Unit tests are provided in `Sigerr.js`, demonstrating the usage and expected behavior of the function.

### External Reference
- For more information on the underlying CSPICE function `sigerr_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/sigerr_c.html).


## `spd` Function Documentation

### Functionality
The `spd` function is a part of the node-gyp implementation that interfaces with the NASA/NAIF CSPICE Library. This function returns the number of seconds in a day, a fundamental constant in time-related computations in astrophysics and space science.

### Usage Example
```javascript
// Call spd to get the number of seconds in a day
const secondsInADay = spice.spd();
```

### Parameters
- The function expects no arguments.

### Return Value
- Returns the number of seconds in a day, as a numeric value.

### Error Handling
- Throws an error if any arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `spd_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spd_c.html).


## `sphrec` Function Documentation

### Functionality
The `sphrec` function converts spherical coordinates (radius, colatitude, and longitude) to rectangular (Cartesian) coordinates.

### Usage Example
```javascript
// Define spherical coordinates
const sph = {"r": 1, "colat": 45.0 * (Math.PI / 180), "slon": 90.0 * (Math.PI / 180)};

// Convert to rectangular coordinates
const rec = spice.sphrec(sph);

// Expect rec = [0, 0.7071, 0.7071]
```

### Parameters
- An object `sph` containing the following key/value pairs:
  - `r`: Radius - distance from the origin.
  - `colat`: Colatitude - angle measured from the positive Z-axis.
  - `slon`: Longitude - angle measured from the positive X-axis in the XY-plane.

### Return Value
- Returns an array of rectangular coordinates `[x, y, z]` corresponding to the input spherical coordinates.

### Error Handling
- Throws an error if incorrect or insufficient arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `sphrec_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/sphrec_c.html).



## `spkcls` Function Documentation

### Functionality
The `spkcls` function closes an open SPK (Spacecraft and Planet Kernel) file identified by its handle.

### Usage Example
```javascript

const handle = spice.spkopenw('new_spk_file.bsp');

spice.spkcls(handle);
// Further write attempts here would fail, as the spk file was closed.
```

### Parameters
- `handle`: An integer representing the handle of the SPK file to be closed.

### Error Handling
- Throws an error if an incorrect or invalid handle is provided.

### External Reference
- For more information on the underlying CSPICE function `spkcls_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkcls_c.html).



## `spkcpo` Function Documentation

### Functionality
The `spkcpo` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, computes the state (position and velocity) of a target body relative to an observer, where the observer's position is specified in a fixed reference frame.

### Usage Example
```javascript
// Define parameters for the SPK "computation of position only" function
const params = {
    target: 'Mars', 
    et: 123456789.0, 
    outref: 'J2000',
    refloc: 'OBSERVER',
    abcorr: 'NONE',
    obspos: [0.0, 0.0, 0.0],
    obsctr: 'Earth',
    obsref: 'J2000'
};

// Compute the state of the target
const {state, lt} = spice.spkcpo(params);

// state is returned as { "r": r, "v": v}
```

### Parameters
- `params`: An object containing the following key/value pairs:
  - `target`: The target body.
  - `et`: The ephemeris time at which the state is to be computed.
  - `outref`: The reference frame in which to express the observer's state.
  - `refloc`: The location to use for the reference point.
  - `abcorr`: The aberration correction flag.
  - `obspos`: The position of the observer in the specified reference frame.
  - `obsctr`: The center of motion of the observer.
  - `obsref`: The reference frame of the observer's state.

### Return Value
- Returns an object containing the target's state and light time (`lt`).

### Error Handling
- Throws an error if incorrect or insufficient arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `spkcpo_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkcpo_c.html).



## `spkcpt` Function Documentation

### Functionality
The `spkcpt` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, computes the state (position and velocity) of a target with constant position in a specified reference frame relative to an observer.

### Usage Example
```javascript
// Define parameters for the SPK "computation of position and time" function
const params = {
    trgpos: [1.0, 2.0, 3.0], 
    trgctr: 'Earth', 
    trgref: 'J2000',
    et: 123456789.0,
    outref: 'J2000',
    refloc: 'OBSERVER',
    abcorr: 'NONE',
    obsrvr: 'Mars'
};

// Compute the state of the target
const {state, lt} = spice.spkcpt(params);
```

### Parameters
- `params`: An object containing the following key/value pairs:
  - `trgpos`: Target position.
  - `trgctr`: Target center.
  - `trgref`: Target reference frame.
  - `et`: The ephemeris time at which the state is to be computed.
  - `outref`: The reference frame in which to express the observer's state.
  - `refloc`: The location to use for the reference point.
  - `abcorr`: The aberration correction flag.
  - `obsrvr`: The observer.

### Return Value
- Returns an object containing the target's state and light time (`lt`).

### Error Handling
- Throws an error if incorrect or insufficient arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `spkcpt_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkcpt_c.html).



## `spkcvo` Function Documentation

### Functionality
The `spkcvo` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, computes the state (position and velocity) of a target body relative to an observer. The observer has a constant velocity in a specified reference frame.

### Usage Example
```javascript
// Define parameters for the SPK "computation of velocity only" function
const params = {
    target: 'Mars', 
    et: 123456789.0, 
    outref: 'J2000',
    refloc: 'OBSERVER',
    abcorr: 'NONE',
    obssta: [0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
    obsepc: 123456789.0,
    obsctr: 'Earth',
    obsref: 'J2000'
};

// Compute the state of the target
const {state, lt} = spice.spkcvo(params);
```

### Parameters
- `params`: An object containing the following key/value pairs:
  - `target`: The target body.
  - `et`: The ephemeris time at which the state is to be computed.
  - `outref`: The reference frame in which to express the observer's state.
  - `refloc`: The location to use for the reference point.
  - `abcorr`: The aberration correction flag.
  - `obssta`: The state of the observer in the specified reference frame.
  - `obsepc`: The ephemeris time associated with `obssta`.
  - `obsctr`: The center of motion of the observer.
  - `obsref`: The reference frame of the observer's state.

### Return Value
- Returns an object containing the target's state and light time (`lt`).

### Error Handling
- Throws an error if incorrect or insufficient arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `spkcvo_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkcvo_c.html).



## `spkcvt` Function Documentation

### Functionality
The `spkcvt` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, computes the state (position and velocity) of a target body having constant velocity in a specified reference frame relative to an observer.

### Usage Example
```javascript
// Define parameters for the SPK "computation of velocity and time" function
const params = {
    trgsta: [1.0, 2.0, 3.0, 0.1, 0.2, 0.3],
    trgepc: 123456789.0,
    trgctr: 'Earth',
    trgref: 'J2000',
    et: 123456789.0,
    outref: 'J2000',
    refloc: 'OBSERVER',
    abcorr: 'NONE',
    obsrvr: 'Mars'
};

// Compute the state of the target
const {state, lt} = spice.spkcvt(params);
```

### Parameters
- `params`: An object containing the following key/value pairs:
  - `trgsta`: The state of the target.
  - `trgepc`: The ephemeris time associated with `trgsta`.
  - `trgctr`: The center of motion of the target.
  - `trgref`: The reference frame of the target's state.
  - `et`: The ephemeris time at which the state is to be computed.
  - `outref`: The reference frame in which to express the observer's state.
  - `refloc`: The location to use for the reference point.
  - `abcorr`: The aberration correction flag.
  - `obsrvr`: The observer.

### Return Value
- Returns an object containing the target's state and light time (`lt`).

### Error Handling
- Throws an error if incorrect or insufficient arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `spkcvt_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkcvt_c.html).


## `spkezr` Function Documentation

### Functionality
The `spkezr` function is a part of the node-gyp implementation wrapping the NASA/NAIF CSPICE Library. It computes the state (position and velocity) of a target body relative to an observing body, corrected for light time and stellar aberration if necessary.

### Usage Example
```javascript
// Define parameters for the SPK "state from ephemeris and observer" function
const params = {
    targ: 'Mars', 
    et: 123456789.0, 
    ref: 'J2000',
    abcorr: 'NONE',
    obs: 'Earth'
};

// Compute the state of the target
const {state, lt} = spice.spkezr(params);
```

### Parameters
- `params`: An object containing the following key/value pairs:
  - `targ`: The target body.
  - `et`: The ephemeris time at which the state is to be computed.
  - `ref`: The reference frame in which to express the state.
  - `abcorr`: The aberration correction flag.
  - `obs`: The observing body.

### Return Value
- Returns an object containing the target's state and light time (`lt`).

### Error Handling
- Throws an error if incorrect or insufficient arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `spkezr_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkpos_c.html).


## `spkgeo` Function Documentation

### Functionality
The `spkgeo` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, computes the geometric state (position and velocity) of a target body relative to an observing body in a specified reference frame.

### Usage Example
```javascript
// Define parameters for the SPK "geometric state" function
const params = {
    targ: 499, // Mars
    et: 123456789.0,
    ref: 'J2000',
    obs: 399 // Earth
};

// Compute the geometric state of the target
const {state, lt} = spice.spkgeo(params);
```

### Parameters
- `params`: An object containing the following key/value pairs:
  - `targ`: The NAIF ID of the target body.
  - `et`: The ephemeris time at which the state is to be computed.
  - `ref`: The reference frame in which to express the state.
  - `obs`: The NAIF ID of the observing body.

### Return Value
- Returns an object containing the target's state and light time (`lt`).

### Error Handling
- Throws an error if incorrect or insufficient arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `spkgeo_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkgeo_c.html).


## `spkgps` Function Documentation

### Functionality
The `spkgps` function is part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library. It computes the geometric position of a target body relative to an observing body in a specified reference frame, corrected for light time if necessary.

### Usage Example
```javascript
// Define parameters for the SPK "geometric position" function
const params = {
    targ: 499, // Mars
    et: 123456789.0,
    ref: 'J2000',
    obs: 399 // Earth
};

// Compute the geometric position of the target
const {pos, lt} = spice.spkgps(params);

// Example assertion to check the correctness
expect(pos).to.be.an('array').with.lengthOf(3);
expectAlmostEqual(lt, 12345.678, 1e-3);
```

### Parameters
- `params`: An object containing the following key/value pairs:
  - `targ`: The NAIF ID of the target body.
  - `et`: The ephemeris time at which the position is to be computed.
  - `ref`: The reference frame in which to express the position.
  - `obs`: The NAIF ID of the observing body.

### Return Value
- Returns an object containing the target's position (`pos`) and light time (`lt`).

### Error Handling
- Throws an error if incorrect or insufficient arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `spkgps_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkgps_c.html).


## `spkobj` Function Documentation

### Functionality
The `spkobj` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, finds the set of ID codes of all objects in a specified SPK (Spacecraft and Planet Kernel) file.

### Usage Example
```javascript
// Define the SPK file name
const spkFileName = 'example.spk';

// Find the set of ID codes in the SPK file
const objectIds = spice.spkobj(spkFileName);

// An array of ID codes should be returned. e.g, [1, 2, 3, 4, ...]
```

### Parameters
- `spkFileName`: A string representing the name of the SPK file.

### Return Value
- Returns an array of ID codes for all objects found in the specified SPK file.

### Error Handling
- Throws an error if incorrect arguments are provided or if the SPK file cannot be accessed.

### External Reference
- For more information on the underlying CSPICE function `spkobj_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkobj_c.html).


## `spkopn` Function Documentation

### Functionality
The `spkopn` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, opens a new SPK (Spacecraft and Planet Kernel) file for writing.

### Usage Example
```javascript
// Define parameters to create a new SPK file
const fileName = 'new_spk_file.bsp';
const internalFileName = 'Internal Name';
const numberOfCommentCharacters = 1024;

// Create the new SPK file
const handle = spice.spkopn(fileName, internalFileName, numberOfCommentCharacters);

// if no exception was thrown, handle will return as a 32-bit integer;
```

### Parameters
- `fileName`: The name of the new SPK file.
- `internalFileName`: The internal file name for the SPK file.
- `numberOfCommentCharacters`: The number of comment characters to allocate.

### Return Value
- Returns a handle to the newly created SPK file.

### Error Handling
- Throws an error if incorrect arguments are provided or if the file cannot be opened.

### External Reference
- For more information on the underlying CSPICE function `spkopn_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkopn_c.html).


## `spkpos` Function Documentation

### Functionality
The `spkpos` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, computes the position of a target body relative to an observing body, corrected for light time and stellar aberration if necessary.

### Usage Example
```javascript
// Define parameters for the SPK "position" function
const params = {
    targ: 'Mars', 
    et: 123456789.0, 
    ref: 'J2000',
    abcorr: 'NONE',
    obs: 'Earth'
};

// Compute the position of the target
const {pos, lt} = spice.spkpos(params);
```

### Parameters
- `params`: An object containing the following key/value pairs:
  - `targ`: The target body.
  - `et`: The ephemeris time at which the position is to be computed.
  - `ref`: The reference frame in which to express the position.
  - `abcorr`: The aberration correction flag.
  - `obs`: The observing body.

### Return Value
- Returns an object containing the target's position (`pos`) and light time (`lt`).

### Error Handling
- Throws an error if incorrect or insufficient arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `spkpos_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkpos_c.html).


## `spkw05` Function Documentation

### Functionality
The `spkw05` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, writes an SPK (Spacecraft and Planet Kernel) segment of type 5, which contains ephemeris data for a specified body.

### Usage Example
```javascript
// Define parameters to write an SPK segment of type 5
const handle = spice.spkopn('new_spk_file.bsp', 'Internal Name', 1024);
const body = 399; // Earth
const center = 10; // Sun
const frame = 'J2000';
const first = 0.0; // Start time
const last = 86400.0; // End time
const segid = 'Segment ID';
const gm = 398600.435436; // GM for Earth
const data = [{state: {r: [x, y, z], v: [dx, dy, dz]}, et: et}, ...]; // Ephemeris data

// Write the segment
spice.spkw05(handle, body, center, frame, first, last, segid, gm, data);
```

### Parameters
- `handle`: The handle of the SPK file to which the segment is to be written.
- `body`: The NAIF ID of the body.
- `center`: The NAIF ID of the center body.
- `frame`: The reference frame.
- `first`, `last`: The start and end times of the segment.
- `segid`: The segment identifier.
- `gm`: The gravitational parameter.
- `data`: An array of state and epoch pairs.

### Return Value
- The function does not return a value but writes the segment to the SPK file.

### Error Handling
- Throws an error if incorrect arguments are provided or if there is an issue with writing to the file.

### External Reference
- For more information on the underlying CSPICE function `spkw05_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkw05_c.html).



## `str2et` Function Documentation

### Functionality
The `str2et` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, converts a time string to ephemeris time (ET), which is the number of seconds past the J2000 epoch.

### Usage Example
```javascript
// Define a time string
const timeString = 'Jan 1, 2023 12:00:00 TDB';

// Convert the time string to ephemeris time
const et = spice.str2et(timeString);
```

### Parameters
- `timeString`: A string representing a time in any format recognized by SPICE.

### Return Value
- Returns the ephemeris time (ET) as a numeric value, corresponding to the input time string.

### Error Handling
- Throws an error if the time string is not in a recognizable format or if other issues occur during conversion.

### External Reference
- For more information on the underlying CSPICE function `str2et_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/str2et_c.html).



## `sxform` Function Documentation

### Functionality
The `sxform` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, computes the state transformation matrix from one reference frame to another at a specified epoch.

### Usage Example
```javascript
// Define parameters for the state transformation matrix computation
const fromFrame = 'IAU_EARTH';
const toFrame = 'J2000';
const ephemerisTime = 123456789.0; // Example ephemeris time

// Compute the state transformation matrix
const stateTransformMatrix = spice.sxform(fromFrame, toFrame, ephemerisTime);

// stateTransformMatrix will be a 6 x 6 array.
```

### Parameters
- `fromFrame`: The name of the reference frame to transform from.
- `toFrame`: The name of the reference frame to transform to.
- `ephemerisTime`: The ephemeris time at which the transformation is computed.

### Return Value
- Returns a 6x6 state transformation matrix.

### Error Handling
- Throws an error if incorrect arguments are provided or if the transformation cannot be computed.

### External Reference
- For more information on the underlying CSPICE function `sxform_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/sxform_c.html).


## `timout` Function Documentation

### Functionality
The `timout` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, converts an input epoch represented in TDB seconds past the TDB epoch of J2000 to a character string formatted according to a user's format picture.

### Usage Example
```javascript
// Define an ephemeris time and a format picture
const et = 757234367.172871; // Example ephemeris time
const formatPicture = 'MON DD,YYYY HR:MN:SC.#### (TDB) ::TDB';

// Convert the ephemeris time to a formatted string
const formattedTime = spice.timout(et, formatPicture);

// formattedTime is now 'DEC 30,2023 18:52:47.1728 (TDB)'
```

### Parameters
- `et`: The ephemeris time in TDB seconds past the J2000 epoch.
- `formatPicture`: A string specifying the format for the output string.

### Return Value
- Returns a formatted time string according to the specified format.

### Error Handling
- Throws an error if incorrect arguments are provided or if the formatting fails.

### External Reference
- For more information on the underlying CSPICE function `timout_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/timout_c.html).


## `twopi` Function Documentation

### Functionality
The `twopi` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, returns the value of \(2\pi\) (twice the value of pi).

### Usage Example
```javascript
// Call twopi to get the value of 2*pi
const twoPiValue = spice.twopi();
```

### Parameters
- The function expects no arguments.

### Return Value
- Returns the numeric value of \(2\pi\).

### Error Handling
- Throws an error if any arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `twopi_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/twopi_c.html).


## `unload` Function Documentation

### Functionality
The `unload` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, unloads a SPICE kernel from the kernel pool.

### Usage Example
```javascript
// Define the path of the SPICE kernel to unload
const kernelPath = 'path/to/spice_kernel.bsp';

// Unload the specified kernel
spice.unload(kernelPath);

```

### Parameters
- `kernelPath`: A string representing the path to the kernel file to be unloaded.

### Return Value
- The function does not return a value but unloads the specified kernel from the pool.

### Error Handling
- Throws an error if incorrect arguments are provided or if the kernel cannot be unloaded.

### External Reference
- For more information on the underlying CSPICE function `unload_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/unload_c.html).



## `vadd` Function Documentation

### Functionality
The `vadd` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, adds two double precision 3-dimensional vectors.

### Usage Example
```javascript
// Define two 3-dimensional vectors
const vector1 = [1, 2, 3];
const vector2 = [1, 1, 1];

// Perform vector addition
const resultVector = spice.vadd(vector1, vector2);

// expefcted result: [2, 3, 4];
```

### Parameters
- `vector1`: The first 3-dimensional vector.
- `vector2`: The second 3-dimensional vector.

### Return Value
- Returns the result of vector addition as a 3-dimensional vector.

### Error Handling
- Throws an error if incorrect arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `vadd_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vadd_c.html).


## `vcrss` Function Documentation

### Functionality
The `vcrss` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, computes the cross product of two 3-dimensional vectors.

### Usage Example
```javascript
// Define two 3-dimensional vectors
const vector1 = [0, 1, 0];
const vector2 = [1, 0, 0];

// Compute the cross product
const crossProduct = spice.vcrss(vector1, vector2);

// Expect [0, 0, -1];
```

### Parameters
- `vector1`: The first 3-dimensional vector.
- `vector2`: The second 3-dimensional vector.

### Return Value
- Returns the cross product of the two vectors as a 3-dimensional vector.

### Error Handling
- Throws an error if incorrect arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `vcrss_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vcrss_c.html).



## `vdist` Function Documentation

### Functionality
The `vdist` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, calculates the distance between two 3-dimensional vectors.

### Usage Example
```javascript
// Define two 3-dimensional vectors
const vector1 = [1.0, 0.0, 0.0];
const vector2 = [0.0, 1.0, 0.0];

// Calculate the distance between the vectors
const distance = spice.vdist(vector1, vector2);

// expect 1.414214 sqrt(2)
```

### Parameters
- `vector1`: The first 3-dimensional vector.
- `vector2`: The second 3-dimensional vector.

### Return Value
- Returns the distance between the two vectors as a numeric value.

### Error Handling
- Throws an error if incorrect arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `vdist_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vdist_c.html).


## `vdot` Function Documentation

### Functionality
The `vdot` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, computes the dot product of two double precision, 3-dimensional vectors.

### Usage Example
```javascript
// Define two 3-dimensional vectors
const vector1 = [1, 2, 3];
const vector2 = [4, 5, 6];

// Compute the dot product
const dotProduct = spice.vdot(vector1, vector2);

// Exptected result is 1*4 + 2*5 + 3*6 = 32
```

### Parameters
- `vector1`: The first 3-dimensional vector.
- `vector2`: The second 3-dimensional vector.

### Return Value
- Returns the dot product of the two vectors as a numeric value.

### Error Handling
- Throws an error if incorrect arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `vdot_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vdot_c.html).


## `vequ` Function Documentation

### Functionality
The `vequ` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, makes one double precision 3-dimensional vector equal to another.

### Usage Example
```javascript
// Define a 3-dimensional vector
const vin = [1, 2, 3];

// Make a new vector equal to the original
const resultVector = spice.vequ(vin);

// expected resultVector = [1, 2, 3];
```

### Parameters
- `vin`: The original 3-dimensional vector.

### Return Value
- Returns a new 3-dimensional vector that is equal to the original vector.

### Error Handling
- Throws an error if incorrect arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `vequ_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vequ_c.html).


## `vhat` Function Documentation

### Functionality
The `vhat` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, finds the unit vector along a double precision 3-dimensional vector.

### Usage Example
```javascript
// Define a 3-dimensional vector
const vector = [5.0, 12.0, 0.0];

// Compute the unit vector
const unitVector = spice.vhat(vector);

//  expected UnitVector = [0.38461538, 0.92307692, 0.00000000];
```

### Parameters
- `vector`: The original 3-dimensional vector.

### Return Value
- Returns the unit vector along the direction of the original vector.

### Error Handling
- Throws an error if incorrect arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `vhat_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vhat_c.html).



## `vlcom` Function Documentation

### Functionality
The `vlcom` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, computes a vector linear combination of two double precision, 3-dimensional vectors.

### Usage Example
```javascript
// Define scalar coefficients and 3-dimensional vectors
const a = 1;
const v1 = [1, 2, 3];
const b = 2;
const v2 = [4, 5, 6];

// Compute the vector linear combination
const linearCombination = spice.vlcom(a, v1, b, v2);

// expected linearCombination = [1*1 + 2*4, 1*2 + 2*5, 1*3 + 2*6] - [9, 12, 15]
```

### Parameters
- `a`: The scalar coefficient for the first vector.
- `v1`: The first 3-dimensional vector.
- `b`: The scalar coefficient for the second vector.
- `v2`: The second 3-dimensional vector.

### Return Value
- Returns the vector linear combination as a 3-dimensional vector.

### Error Handling
- Throws an error if incorrect arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `vlcom_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vlcom_c.html).


## `vlcom3` Function Documentation

### Functionality
The `vlcom3` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, computes the vector linear combination of three double precision, 3-dimensional vectors.

### Usage Example
```javascript
// Define scalar coefficients and 3-dimensional vectors
const a = 1;
const v1 = [1, 2, 3];
const b = 2;
const v2 = [4, 5, 6];
const c = 3;
const v3 = [7, 8, 9];

// Compute the vector linear combination
const linearCombination = spice.vlcom3(a, v1, b, v2, c, v3);
// expected linearCombination = [1*1 + 2*4 + 3*7, 1*2 + 2*5 + 3*8, 1*3 + 2*6 + 3*9] - [34, 40, 46]

```

### Parameters
- `a`, `b`, `c`: The scalar coefficients for the vectors.
- `v1`, `v2`, `v3`: The 3-dimensional vectors.

### Return Value
- Returns the vector linear combination as a 3-dimensional vector.

### Error Handling
- Throws an error if incorrect arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `vlcom3_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vlcom3_c.html).


## `vminus` Function Documentation

### Functionality
The `vminus` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, negates a double precision 3-dimensional vector.

### Usage Example
```javascript
// Define a 3-dimensional vector
const vector = [1, 2, 3];

// Negate the vector
const negatedVector = spice.vminus(vector);

// expect NegatedVector = [-1, -2, -3];
```

### Parameters
- `vector`: The original 3-dimensional vector.

### Return Value
- Returns the negated vector as a 3-dimensional vector.

### Error Handling
- Throws an error if incorrect arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `vminus_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vminus_c.html).



## `vnorm` Function Documentation

### Functionality
The `vnorm` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, computes the magnitude of a double precision 3-dimensional vector.

### Usage Example
```javascript
// Define a 3-dimensional vector
const vector = [1, 2, 2];

// Compute the magnitude of the vector
const magnitude = spice.vnorm(vector);

// expect magnitude = sqrt(1^2 + 2^2 + 2^2)

```

### Parameters
- `vector`: The 3-dimensional vector.

### Return Value
- Returns the magnitude of the vector as a numeric value.

### Error Handling
- Throws an error if incorrect arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `vnorm_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vnorm_c.html).



## `vpack` Function Documentation

### Functionality
The `vpack` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, packs three scalar components into a 3-dimensional vector.

### Usage Example
```javascript
// Define three scalar components
const x = -1;
const y = -2;
const z = -3;

// Pack them into a vector
const vector = spice.vpack(x, y, z);

// expect vector = [-1, -2, -3];
```

### Parameters
- `x`: The x-component of the vector.
- `y`: The y-component of the vector.
- `z`: The z-component of the vector.

### Return Value
- Returns a 3-dimensional vector array `[x, y, z]`.

### Error Handling
- Throws an error if incorrect arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `vpack_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vpack_c.html).


## `vpack` Function Documentation

### Functionality
The `vpack` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, packs three scalar components into a 3-dimensional vector.

### Usage Example
```javascript
// Define three scalar components
const x = -1;
const y = -2;
const z = -3;

// Pack them into a vector
const vector = spice.vpack(x, y, z);

// expected vector = [-1, -2, -3];
```

### Parameters
- `x`: The x-component of the vector.
- `y`: The y-component of the vector.
- `z`: The z-component of the vector.

### Return Value
- Returns a 3-dimensional vector array `[x, y, z]`.

### Error Handling
- Throws an error if incorrect arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `vpack_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vpack_c.html).



## `vprjp` Function Documentation

### Functionality
The `vprjp` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, projects a vector onto a specified plane orthogonally.

### Usage Example
```javascript
// Define the normal and origin of a plane
const norm = [0, 0, 1];
const orig = [0, 0, 0];

// Create the plane
const plane = spice.nvp2pl(norm, orig);

// Define a vector
const vector = [-29703.16955, 879765.72163, -12345.6789];

// Project the vector onto the plane
const projectedVector = spice.vprjp(vector, plane);

//  expected projectedVector = [-29703.16955, 879765.72163, 0];
```

### Parameters
- `vin`: The 3-dimensional vector to be projected.
- `plane`: The plane onto which the vector is projected, defined by its normal and origin.

### Return Value
- Returns the orthogonal projection of the vector onto the specified plane.

### Error Handling
- Throws an error if incorrect arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `vprjp_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vprjp_c.html).


## `vprjpi` Function Documentation

### Functionality
The `vprjpi` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, finds the vector in a specified plane that maps to a specified vector in another plane under orthogonal projection.

### Usage Example
```javascript
// Define a vector and two planes
const vin = [0, 1, 0];
const projpl = spice.nvc2pl([0,0,1], 0); // Plane perpendicular to Z-axis
const invpl = spice.nvc2pl([0,1,0], 0);  // Plane perpendicular to Y-axis

// Find the vector in the invpl plane that maps to vin in the projpl plane
const {vout, found} = spice.vprjpi(vin, projpl, invpl);

// expected Vout = [1, 0, 0], found = true
```

### Parameters
- `vin`: The 3-dimensional vector.
- `projpl`: The plane in which `vin` is considered.
- `invpl`: The plane in which the output vector is to be found.

### Return Value
- Returns an object containing the resulting vector and a boolean indicating if the vector was found.

### Error Handling
- Throws an error if incorrect arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `vprjpi_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vprjpi_c.html).


## `vproj` Function Documentation

### Functionality
The `vproj` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, computes the projection of one 3-dimensional vector onto another 3-dimensional vector.

### Usage Example
```javascript
// Define two 3-dimensional vectors
const a = [6, 6, 6];
const b = [2, 0, 0];

// Compute the projection of vector 'a' onto vector 'b'
const projectedVector = spice.vproj(a, b);

// expected projectedVector = [6, 0, 0]; // Projection of 'a' onto 'b'
```

### Parameters
- `a`: The first 3-dimensional vector.
- `b`: The second 3-dimensional vector, onto which `a` is projected.

### Return Value
- Returns the projection of `a` onto `b` as a 3-dimensional vector.

### Error Handling
- Throws an error if incorrect arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `vproj_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vproj_c.html).



## `vrel` Function Documentation

### Functionality
The `vrel` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, computes the relative difference between two double precision, 3-dimensional vectors.

### Usage Example
```javascript
// Define two 3-dimensional vectors
const v1 = [1, 2, 3];
const v2 = [4, 5, 6];

// Compute the relative difference between the vectors
const relativeDifference = spice.vrel(v1, v2);

// expected relativeDifference = 0.592156525463792
```

### Parameters
- `v1`: The first 3-dimensional vector.
- `v2`: The second 3-dimensional vector.

### Return Value
- Returns the relative difference between `v1` and `v2` as a numeric value.

### Error Handling
- Throws an error if incorrect arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `vrel_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vrel_c.html).


## `vrotv` Function Documentation

### Functionality
The `vrotv` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, rotates a vector about a specified axis vector by a specified angle.

### Usage Example
```javascript
// Define a vector, axis of rotation, and rotation angle
const v = [1, 2, 3];
const axis = [0, 0, 1]; // Z-axis
const theta = spice.halfpi(); // 90 degrees

// Rotate the vector about the axis by the angle
const rotatedVector = spice.vrotv(v, axis, theta);

// expected rotatedVector = [-2, 1, 3];
```

### Parameters
- `v`: The 3-dimensional vector to be rotated.
- `axis`: The 3-dimensional axis vector about which the rotation is performed.
- `theta`: The rotation angle in radians.

### Return Value
- Returns the rotated vector as a 3-dimensional vector.

### Error Handling
- Throws an error if incorrect arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `vrotv_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vrotv_c.html).


## `vscl` Function Documentation

### Functionality
The `vscl` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, multiplies a scalar value with a double precision 3-dimensional vector.

### Usage Example
```javascript
// Define a scalar and a 3-dimensional vector
const s = 2;
const v1 = [1, 2, 3];

// Perform scalar multiplication
const scaledVector = spice.vscl(s, v1);

// expected scaledVector = [2, 4, 6]
```

### Parameters
- `s`: The scalar value.
- `v1`: The original 3-dimensional vector.

### Return Value
- Returns the scaled vector as a 3-dimensional array.

### Error Handling
- Throws an error if incorrect arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `vscl_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vscl_c.html).



## `vsep` Function Documentation

### Functionality
The `vsep` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, computes the separation angle in radians between two double precision, 3-dimensional vectors.

### Usage Example
```javascript
// Define two 3-dimensional vectors
const v1 = [1, 0, 0];
const v2 = [0, 1, 0];

// Compute the separation angle between the vectors
const separationAngle = spice.vsep(v1, v2);

// expected separationAngle = Math.PI / 2 -  90 degrees (in radians)
```

### Parameters
- `v1`: The first 3-dimensional vector.
- `v2`: The second 3-dimensional vector.

### Return Value
- Returns the separation angle in radians between the two vectors.

### Error Handling
- Throws an error if incorrect arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `vsep_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vsep_c.html).



## `vsub` Function Documentation

### Functionality
The `vsub` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, computes the difference between two double precision, 3-dimensional vectors.

### Usage Example
```javascript
// Define two 3-dimensional vectors
const v1 = [1, 2, 3];
const v2 = [1, 1, 1];

// Compute the difference between the vectors
const differenceVector = spice.vsub(v1, v2);

// expected differenceVector = [0, 1, 2]
```

### Parameters
- `v1`: The first 3-dimensional vector.
- `v2`: The second 3-dimensional vector.

### Return Value
- Returns the difference between `v1` and `v2` as a 3-dimensional vector.

### Error Handling
- Throws an error if incorrect arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `vsub_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vsub_c.html).



## `vtmv` Function Documentation

### Functionality
The `vtmv` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, multiplies the transpose of a 3-dimensional column vector, a 3x3 matrix, and a 3-dimensional column vector, in that order.

### Usage Example
```javascript
// Define a 3-dimensional vector, a 3x3 matrix, and another 3-dimensional vector
const v1 = [2, 4, 6];
const matrix = [[0, 1, 0], [-1, 0, 0], [0, 0, 1]];
const v2 = [1, 1, 1];

// Perform the matrix multiplication
const result = spice.vtmv(v1, matrix, v2);

// expected result = 4
```

### Parameters
- `v1`: The first 3-dimensional column vector.
- `matrix`: The 3x3 matrix.
- `v2`: The second 3-dimensional column vector.

### Return Value
- Returns the result of the matrix multiplication as a numeric value.

### Error Handling
- Throws an error if incorrect arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `vtmv_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vtmv_c.html).


## `vupack` Function Documentation

### Functionality
The `vupack` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, unpacks three scalar components from a double precision, 3-dimensional vector.

### Usage Example
```javascript
// Define a 3-dimensional vector
const v = [1, 2, 3];

// Unpack the scalar components from the vector
const { x, y, z } = spice.vupack(v);

// expected Components = "x":1, "y":2, "z":3
```

### Parameters
- `v`: The 3-dimensional vector to unpack.

### Return Value
- Returns an object with the scalar components `x`, `y`, and `z` of the vector.

### Error Handling
- Throws an error if incorrect arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `vupack_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vupack_c.html).


## `vzero` Function Documentation

### Functionality
The `vzero` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, checks if a double precision, 3-dimensional vector is the zero vector.

### Usage Example
```javascript
// Define a 3-dimensional vector
const vector = [0, 0, 0];

// Check if the vector is the zero vector
const isZero = spice.vzero(vector);

// expect isZero === true
```

### Parameters
- `vector`: The 3-dimensional vector to check.

### Return Value
- Returns a boolean value `true` if the vector is the zero vector, otherwise `false`.

### Error Handling
- Throws an error if incorrect arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `vzero_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vzero_c.html).



## `xpose` Function Documentation

### Functionality
The `xpose` function, part of a node-gyp implementation wrapping the NASA/NAIF CSPICE Library, transposes a 3x3 double precision matrix.

### Usage Example
```javascript
// Define a 3x3 matrix
const matrix = [[0, -1, 0], [0.5, 0, 0], [0, 0, 1]];

// Transpose the matrix
const transposedMatrix = spice.xpose(matrix);

// expected transposedMatrix = [[0, 0.5, 0], [-1, 0, 0], [0, 0, 1]];
```

### Parameters
- `matrix`: The 3x3 matrix to be transposed.

### Return Value
- Returns the transposed 3x3 matrix.

### Error Handling
- Throws an error if incorrect arguments are provided.

### External Reference
- For more information on the underlying CSPICE function `xpose_c`, refer to [NASA/NAIF Toolkit Documentation](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/xpose_c.html).

## Utility functions

`js-spice` includes a few utility function that are useful when working with the module and for downloading kernel files.



### `cacheGenericKernel` Function Documentation

#### Functionality
The `cacheGenericKernel` function asynchronously downloads a file from a specified URL and saves it to a given directory. This function operates asynchronously and returns a Promise. It should be used with 'await' in an async function context, or with `.then()`/`.catch()` to properly handle the asynchronous operation. The function skips the download if the file already exists. If 'dirRelative' is not provided, the file is saved using 'urlRelative' as a relative path. Upon successful download, or if the file already exists, it returns the absolute path of the file on the local file system.

#### Usage Example
```javascript
const { downloadKernel } = require('js-spice');

// Async function to download and cache a kernel
async function downloadKernel() {
  const urlRelative = 'path/to/kernel';
  const dirRelative = 'directory/to/save';

  try {
    const filePath = await cacheGenericKernel(urlRelative, dirRelative);
    console.log(`Kernel saved at: ${filePath}`);
  } catch (error) {
    console.error(`Error downloading kernel: ${error.message}`);
  }

  // now you can use the kernel file (supply it to furnsh, etc)
  // ...
}

// Call the async function
downloadKernel();
```

#### Parameters
- `urlRelative`: The relative URL path from the base URL.
- `dirRelative`: (Optional) The relative directory path from the base directory.

#### Return Value
- Returns a Promise that resolves to the absolute path of the file on the local file system.

#### Error Handling
- Logs and throws an error if there are issues during the download process.

#### Reminder
- Remember that this is an asynchronous function. Use `await` within an async function, or `.then()`/`.catch()` for handling the Promise.

#### External Reference
- Utilizes Axios for HTTP requests and Node.js File System (fs) module for handling files.



### `et_now` Function Documentation

#### Functionality
The `et_now` function retrieves the current time in Ephemeris Time (ET) format using the SPICE toolkit. Ephemeris Time is a time scale commonly used in planetary science, especially for solar system dynamics.

#### Usage Example
```javascript
const {et_now} = require('js-spice');

// Retrieve the current time in Ephemeris Time (ET) format
const currentET = et_now();

```

#### Parameters
- The function expects no arguments.

#### Return Value
- Returns the current time in Ephemeris Time (ET) format as a numeric value.

#### Error Handling
- The function relies on SPICE's `str2et` for time conversion, which may throw an error for invalid time formats or other internal issues.

#### External Reference
- This function utilizes the `str2et` function from the SPICE toolkit for the time conversion. More information on the `str2et` function can be found in the SPICE toolkit documentation.


### `getGeophysicalConstants` Function Documentation

#### Functionality
The `getGeophysicalConstants` function asynchronously retrieves geophysical constants for Earth using the SPICE toolkit. The function operates asynchronously and returns a Promise. It should be used with 'await' in an async function context or with `.then()`/`.catch()` to handle the asynchronous operation properly. If `getCachedKernel` is true, the function ensures the specified kernel file is downloaded and available before fetching constants.

#### Usage Example
```javascript
const { getGeophysicalConstants } = require('js-spice');

// Async function to retrieve geophysical constants
async function retrieveConstants() {
  try {
    const constants = await getGeophysicalConstants(true);
    console.log(`Geophysical Constants: `, constants);
  } catch (error) {
    console.error(`Error retrieving constants: ${error.message}`);
  }

  // geophysical constants should now be downloaded, cached locally, and supplied to furnsh
}

// Call the async function
retrieveConstants();
```

#### Parameters
- `getCachedKernel`: Flag to determine whether to download and cache the kernel file.
- `kernelToUse`: (Optional) The kernel file to use. Defaults to 'pck/geophysical.ker'.
- `kernelCacheLocation`: (Optional) Location to cache the kernel file. Defaults to 'data/naif/generic_kernels/${file}'.

#### Return Value
- Returns a Promise that resolves to an object containing key geophysical constants such as j2, j3, j4, ke, qo, so, er, ae.

#### Error Handling
- Logs and throws an error if there are issues during the process.

#### Reminder
- Remember that this is an asynchronous function. Use `await` within an async function, or `.then()`/`.catch()` for handling the Promise.

#### External Reference
- Utilizes SPICE toolkit functions for fetching geophysical constants.



### `getKernels` Function Documentation

#### Functionality
The `getKernels` function asynchronously loads and processes SPICE kernel files, returning a Promise. It should be used with 'await' or `.then()` to properly handle the asynchronous operation. The function checks if the provided `kernelsToLoad` is a string or an array, and then proceeds to load and process each kernel file. If `kernelCacheLocation` is not provided, it defaults to 'data/naif/generic_kernels'.

#### Usage Example

```javascript
const { getKernels } = require('js-spice');

// Async function to load kernel files
async function loadKernels() {
  const kernels = ['spk/planets.bsp', 'lsk/naif0012.tls'];
  try {
    await getKernels(kernels);
    console.log('Kernels loaded successfully.');
  } catch (error) {
    console.error(`Error loading kernels: ${error.message}`);
  }

  // the kernels should now be downloaded, locally cached, and furnsh'ed.
  // ...
}

// Call the async function
loadKernels();
```

#### Parameters
- `kernelsToLoad`: The kernel file(s) to load. Can be a string or an array of strings.
- `kernelCacheLocation`: (Optional) The location where the kernel cache is stored. Defaults to 'data/naif/generic_kernels' if not specified.

#### Return Value
- Returns a Promise that resolves when the kernel files are loaded and processed.

#### Error Handling
- Logs and throws an error if there are issues during the process.

#### Reminder
- Remember that this is an asynchronous function. Use `await` within an async function, or `.then()` for handling the Promise.

#### External Reference
- Utilizes the `cacheGenericKernel` function to cache and `spice.furnsh` to process the kernel files.


### Extending `js-spice` to wrap additional SPICE functions

Additional SPICE functions can be be wrapped for JavaScript use if you add a C++ implementation.  To add a new function, copy the implementation of an existing function. It should be (mostly) apparent how to modify the code to wrap the new function.

Example implementation:
```cpp
#include "wrapped/spkgeo.h"
#include "utility/err.h"

extern "C" {
  #include <SpiceUsr.h>
}
#include "utility/pack.h"
#include "utility/unpack.h"

Napi::Value spkgeo(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    // Parameters that will be passed into SPICE
    SpiceInt targ, obs;
    std::string ref;
    SpiceDouble et;
    
    if(
        // Unpack js parameters into Spice-worthy representations
        Unpack("spkgeo", info)
        
        .i(targ, "targ")  // "i" = unpack the next param as an integer
        .et(et)           // "et" = unpack next param as an ephemeris time
        .str(ref, "ref")  // "str" = unpack next param as a string
        .i(obs, "obs")    // "i" = unpack next param as integer
        
        .check( [=](const std::string& error) {
                // lambda handler for missing/extra args, incorrect types, etc.
                Napi::TypeError::New(env, error).ThrowAsJavaScriptException();
            })){
            return env.Null();
    }

    SpiceDouble     state[6];
    SpiceDouble     lt;
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkgeo_c.html
    spkgeo_c(targ, et, ref.c_str(), obs, state, &lt);

    // Pack return values as an object containing "state" and "lt" children
    // where state is a type state ({r: [x, y, z], v: [dx, dy, dz]})
    // and lt is a double precision numeric.
    // ...with an error check for SPICE errors
    return Pack(info).state(state).as("state").with(lt, "lt").check();
}
```

The next, after authoring your .h and .cpp wrapper, the .cpp will need added to `binding.gyp`.
An include statement for the header will need added to `js-spice.cpp` and a line added to export the newly defined function in the bottom half of the file.  An optional unit test can be added to the /test subdirectory.  The module can then be rebuilt.  If you've installed node-gyp globally you can rebuild via `node-gyp clean configure build` from the `js-spice` directory.  If it's not installed, find the binary node-gyp in the node_modules directory under `js-spice` and invoke it via its full path.


### License
MIT License.
