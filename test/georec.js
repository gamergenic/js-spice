const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('georec', function() {
  it('should convert geodetic coordinates to rectangular coordinates.',
   function() {

    const radius = 6378.2064;
    const f = 1./294.9787;
    const pi = 3.1415926536;
    const rpd = pi / 180;
    const cyl = {"lon": 90.0 * rpd, "lat":0, "alt":0};
    
    const actual = spice.georec(cyl, radius, f);

    const expected = [0.000, 6378.206, 0.000];
    const tolerance = 1e-3;
    expectAlmostEqual(actual, expected, tolerance); 
  });
});
