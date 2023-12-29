const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('cylrec', function() {
  it('should convert from cylindrical to rectangular coordinates.',
   function() {

    const pi = 3.1415926536;
    const rpd = pi / 180;
    const cyl = {"r": 1.4142, "clon":45.0*rpd, "z":1.0};
    
    const actual = spice.cylrec(cyl);

    const expected = [1, 1, 1];
    const tolerance = 1e-4;
    expectAlmostEqual(actual, expected, tolerance); 
  });
});
