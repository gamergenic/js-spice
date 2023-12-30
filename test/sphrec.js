const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('sphrec', function() {
  it('should convert from spherical coordinates to rectangular coordinates.',
   function() {

    const pi = 3.1415926536;
    const rpd = pi / 180;
    const sph = {"r": 1, "colat":45.0*rpd, "slon":90.0*rpd};

    const actual = spice.sphrec(sph);

    const expected = [0,0.7071067811847432,0.7071067811883519];
    const tolerance = 1e-6;
    expectAlmostEqual(actual, expected, tolerance); 
  });
});
