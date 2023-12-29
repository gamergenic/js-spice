const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('eul2m', function() {
  it('should construct a rotation matrix from a set of Euler angles.',
   function() {

    let pi = 3.1415926536;

    const angle3 = 0;
    const angle2 = 0;
    const angle1 = pi / 2;
    const axis3 = 1;
    const axis2 = 1;
    const axis1 = 3;

    const actual = spice.eul2m(angle3, angle2, angle1, axis3, axis2, axis1);

    const expected = [[0, 1, 0], [-1, 0, 0], [0, 0, 1]];
    const tolerance = 1e-8;

    expectAlmostEqual(actual, expected, tolerance);
  });
});
