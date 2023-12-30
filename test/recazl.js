const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('recazl', function() {
  it('should convert rectangular coordinates of a point to range, azimuth and  elevation.',
   function() {

    const rec = [1, 1, 1];
    
    const actual = spice.recazl(rec, false, false);

    const pi = 3.1415926536;
    const rpd = pi / 180;
    const expected = {"range": 1.732, "az":315*rpd, "el":-35.264*rpd};

    const tolerance = 1e-4;
    expectAlmostEqual(actual, expected, tolerance); 
  });

  it('should convert rectangular coordinates of a point to range, azimuth and  elevation (az ccw, el +z).',
   function() {

    const rec = [1, -1, -1];
    const actual = spice.recazl(rec, true, true);

    const pi = 3.1415926536;
    const rpd = pi / 180;
    const expected = {"range": 1.732, "az":315*rpd, "el":-35.264*rpd};

    const tolerance = 1e-4;
    expectAlmostEqual(actual, expected, tolerance); 
  });  
});
