const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('q2m', function() {
  it('should find the rotation matrix corresponding to a specified unit quaternion',
   function() {
    
    const s = Math.sqrt(2)/2;
    const q = {"x":0, "y":0, "z":-s, "w":s};

    const actual = spice.q2m(q);

    const pi = 3.1415926536;
    const expected = spice.rotate(pi/2, 3);

    const tolerance = 1e-8;
    expectAlmostEqual(actual, expected, tolerance);
  });
});
