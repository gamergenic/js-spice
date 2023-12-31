const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('radrec', function() {
  it('should convert from range, right ascension, and declination to \
rectangular coordinates.',
   function() {

    const pi = 3.1415926536;
    const rpd = pi / 180;
    const rad = {"range": 1, "ra":90.0*rpd, "dec":45.0*rpd};
    
    const actual = spice.radrec(rad);

    const expected = [0,0.7071067811847432,0.7071067811883519];
    const tolerance = 1e-6;
    expectAlmostEqual(actual, expected, tolerance); 
  });
});
