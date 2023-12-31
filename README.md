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
const et = 0;
let actual = spice.pxfrm2('IAU_EARTH', 'J2000', et, et);
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


# `q2m` Function Documentation

## Functionality
The `q2m` function calculates the rotation matrix corresponding to a specified unit quaternion. It is typically used to convert quaternion representations of rotations into matrix form, which is more suitable for certain types of calculations.

## Usage Example
```javascript
const s = Math.sqrt(2) / 2;
const q = {"x": 0, "y": 0, "z": -s, "w": s};

const m = spice.q2m(q);

// m now contains a 3x3 array of matrix values.
```

## Parameters
- `q`: The input quaternion represented as an object with `x`, `y`, `z`, and `w` components.

## Return Value
Returns a 3x3 rotation matrix corresponding to the given quaternion.

## Error Handling
- Throws an error if the input is not a unit quaternion.
- Handles cases where input quaternion components are not in the expected format.

## Note
This function is essential for converting quaternion representations, commonly used in spacecraft attitude control and 3D graphics, into rotation matrices that can be easily used for further geometric transformations.



# `qxq` Function Documentation

## Functionality
The `qxq` function multiplies two quaternions, `q1` and `q2`. This operation is essential in computational geometry, particularly in spacecraft attitude and orientation calculations.

## Usage Example
```javascript
const q1 = {"x":1, "y":0, "z":0, "w":0};
const q2 = {"x":0, "y":1, "z":0, "w":0};

const q_x_q = spice.qxq(q1, q2);
```

## Parameters
- `q1`: The first quaternion.
- `q2`: The second quaternion.

## Return Value
Returns the product of the two quaternions as a new quaternion.

## Error Handling
- Throws an error if incorrect arguments are provided.



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
