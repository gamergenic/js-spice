const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('m2q', function() {
  it('should find a unit quaternion corresponding to a specified rotation matrix.',
   function() {

    let pi = 3.1415926536;

    const r = spice.rotate(pi/2, 3);
    const actual = spice.m2q(r);

    const s = Math.sqrt(2)/2;
    const expected = {"x":0, "y":0, "z":-s, "w":s};
    const tolerance = 1e-8;

    expectAlmostEqual(actual, expected, tolerance);
  });
});
