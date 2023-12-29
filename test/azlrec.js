const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('azlrec', function() {
  it('should convert from range, azimuth and elevation of a point to \
rectangular coordinates.',
   function() {

    const pi = 3.1415926536;
    const rpd = pi / 180;
    const azl = {"range": 1.732, "az":315*rpd, "el":-35.264*rpd};
    
    const actual = spice.azlrec(azl, false, false);

    const expected = [1, 1, 1];
    const tolerance = 1e-4;
    expectAlmostEqual(actual, expected, tolerance); 
  });

  it('should convert from range, azimuth and elevation of a point to \
rectangular coordinates (az ccw, el +z).',
   function() {

    const pi = 3.1415926536;
    const rpd = pi / 180;
    const azl = {"range": 1.732, "az":315*rpd, "el":-35.264*rpd};
    
    const actual = spice.azlrec(azl, true, true);

    const expected = [1, -1, -1];
    const tolerance = 1e-4;
    expectAlmostEqual(actual, expected, tolerance); 
  });  
});
