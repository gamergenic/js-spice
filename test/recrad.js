const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('recrad', function() {
  it('should convert rectangular coordinates to range, right ascension, and declination.',
   function() {

    const rec = [0,0.7071067811847432,0.7071067811883519];
    const actual = spice.recrad(rec);

    const pi = 3.1415926536;
    const rpd = pi / 180;
    const expected = {"range": 1, "ra":90.0*rpd, "dec":45.0*rpd};

    const tolerance = 1e-6;
    expectAlmostEqual(actual, expected, tolerance); 
  });
});
