const expect = require('chai').expect;
const { spice } = require('..');

describe('conics', function() {
    // from https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/prop2b_c.html
    it('should Determine the state (position, velocity) of an orbiting body \
from a set of elliptic, hyperbolic, or parabolic orbital \
elements.', function() {
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

        const oscelts = spice.oscelt(pvinit, et, mu);
    
        let actual = spice.conics(oscelts, et + t);
        let expected = {
            "r": [-0.00000,-70710678.11865,-70710678.11865],
            "v": [0.00000,0.04464,-0.04464]
        };
    
        expect(actual.r[0]).to.be.closeTo(expected.r[0], 0.00001);
        expect(actual.r[1]).to.be.closeTo(expected.r[1], 0.00001);
        expect(actual.r[2]).to.be.closeTo(expected.r[2], 0.00001);
        expect(actual.v[0]).to.be.closeTo(expected.v[0], 0.00001);
        expect(actual.v[1]).to.be.closeTo(expected.v[1], 0.00001);
        expect(actual.v[2]).to.be.closeTo(expected.v[2], 0.00001);        
      });
});
