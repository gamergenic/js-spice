# js-spice

`js-spice` is a Node.js module that provides a JavaScript interface to NASA/JPL/NAIF's CSPICE toolkit, a collection of functions widely used in the planetary science community for spaceflight geometry calculations. Designed primarily for astrophysicists and developers in the field of space exploration, this module enables the integration of CSPICE's robust space mission analysis capabilities into JavaScript applications.

For an example of `js-spice` usage, refer to our web server project that utilizes the module: [Earth-Moon-Sun Simulation](https://github.com/gamergenic/earth-moon-sun). This project illustrates how js-spice can be used for space-related calculations and simulations in a JavaScript environment.

## Ongoing Development Notice

Please note that js-spice is currently under active development. It has not been fully tested and is still evolving. The documentation available at this stage primarily consists of preliminary notes and usage examples. Users are welcome to explore and experiment with the module, but it's important to be aware of its provisional state and ongoing changes.

## Installation Guide

`js-spice` is still in the development phase and has not yet been officially released on npm. To integrate it into your project, you can't currently use the standard npm installation command. Instead, you can include it by linking directly to the GitHub repository as a git submodule. Detailed instructions for this process can be found in the section "Adding js-spice as a git submodule to a host app."


### Testing
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
```

**Fetching Radii with Body ID:**
```javascript
const earth_radii = spice.bodvrd("399", "RADII");
```

**Fetching 1-Dimensional Value:**
```javascript
const earth_long_axis = spice.bodvrd("EARTH", "LONG_AXIS");
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

const rotationMatrix = spice.eul2m({
    angle3, angle2, angle1,
    axis3,  axis2,  axis1
});
```

### Parameters
- An object with the following required keys:
- `angle3`, `angle2`, `angle1`: The three Euler angles (in radians).
- `axis3`, `axis2`, `axis1`: The axes of the rotations.

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
Returns an object containing 'elems', the extracted orbital elements and the epoch of the elements and 'epoch'.  This if of the form:

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

const actual = spice.gfposc(target, frame, abcorr, obsrvr, crdsys, coord, relate, refval, adjust, step, cnfine);
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
Returns an array of time windows when the specified constraint is satisfied.

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








##### georec
    console.log(spice.georec({"lon" : 1, "lat" : -1, "alt" : 1000 }, 10000, 0));

##### latrec
    console.log(spice.latrec({"radius" : 10000, "lon" : 2, "lat" : -1 }));

##### halfpi
    console.log(spice.halfpi());
    console.log(spice.twopi());

##### pgrrec
    console.log(spice.pgrrec("earth", {"lon" : 1, "lat" : -1, "alt" : 10000 }, 6000, 0));

##### pi
    console.log(spice.pi());


##### sphrec
    console.log(spice.sphrec({"r" : 10000, "colat" : 2, "slon" : -1 }));

##### twopi


##### spkezr
https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkezr_c.html

###### Usage
```js
// init js-spice, load kernels
let result = spice.spkezr('moon', spice.str2et("2023 DEC 30"), 'J2000', 'NONE', 'earth');
console.log(result.toString());
```

##### spkpos
###### Usage
```js
// init js-spice, load kernels
let result = spice.spkpos('moon', spice.str2et("2023 DEC 30"), 'J2000', 'NONE', 'earth');
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

##### str2et
###### Usage
```js
const spice = require('js-spice');
spice.unload("C:\\naif\\kernels\\Generic\\LSK\\latest_leapseconds.tls");
```

##### timout

###### Usage
```js
console.log(spice.timout(now(), 'MON DD,YYYY  HR:MN:SC.#### (TDB) ::TDB'));
```

##### unload
###### Usage
```js
const spice = require('js-spice');
spice.unload("C:\\naif\\kernels\\Generic\\LSK\\latest_leapseconds.tls");
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
