const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('reccyl', function() {
  it('should convert from rectangular to cylindrical coordinates.',
   function() {

    const rec = [1, 1, 1];
    const actual = spice.reccyl(rec);
        
    const pi = 3.1415926536;
    const rpd = pi / 180;
    const expected = {"r": 1.4142, "clon":45.0*rpd, "z":1.0};

    const tolerance = 1e-4;
    expectAlmostEqual(actual, expected, tolerance); 
  });
});
