const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('radrec', function() {
  it('should convert from range, right ascension, and declination to \
rectangular coordinates.',
   function() {

    const pi = 3.1415926536;
    const rpd = pi / 180;
    const rad = {"range": 1, "ra":90.0*rpd, "dec":45.0};
    
    const actual = spice.radrec(rad);
    console.log(JSON.stringify(actual));

    const expected = [0,0.5253219888177297,0.8509035245341184];
    const tolerance = 1e-6;
    expectAlmostEqual(actual, expected, tolerance); 
  });
});
