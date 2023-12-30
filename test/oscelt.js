const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('oscelt', function() {
    // from https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/prop2b_c.html
    it('should determine the set of osculating conic orbital elements that \
corresponds to the state (position, velocity) of a body.', function() {

        const mu = 3.9860043543609598e5;
        const r = 1e8;
        const speed = Math.sqrt(mu/r);
        const pi = 3.141592653589793238462643383279502884197;
        const t = pi * r / speed; 
        const pvinit = {
            "r": [0, r/Math.sqrt(2), r/Math.sqrt(2)],
            "v": [0, -speed/Math.sqrt(2), speed/Math.sqrt(2)]
        };
        const et = 0;

        const actual = spice.oscelt(pvinit, et, mu);

        const expected = {
            "rp": 1e8,
            "ecc":0,
            "inc":1.5707963267948966,
            "lnode":1.5707963267948966,
            "argp":0,
            "m0":0.7853981633974484,
            "t0":0,
            "mu":398600.435436096
        };

        const tolerance = 1e-5;
        expectAlmostEqual(actual, expected, tolerance);
      });
});
