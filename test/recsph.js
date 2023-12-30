const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('recsph', function() {
  it('should convert from rectangular coordinates to spherical coordinates.',
   function() {

    const rec = [0,0.7071067811847432,0.7071067811883519];
    const actual = spice.recsph(rec);

    const pi = 3.1415926536;
    const rpd = pi / 180;
    const expected = {"r": 1, "colat":45.0*rpd, "slon":90.0*rpd};

    const tolerance = 1e-6;
    expectAlmostEqual(actual, expected, tolerance); 
  });
});
