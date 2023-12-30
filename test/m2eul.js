const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('m2eul', function() {
  it('should factor a rotation matrix as a product of three rotations about \
specified coordinate axes.',
   function() {

    let pi = 3.1415926536;

    const r = [[0, 1, 0], [-1, 0, 0], [0, 0, 1]];
    const angle3 = 0;
    const angle2 = 0;
    const angle1 = pi / 2;
    const axis3 = 1;
    const axis2 = 2;
    const axis1 = 3;

    const actual = spice.m2eul(r, axis3, axis2, axis1);

    const expected = {angle3, angle2, angle1, axis3, axis2, axis1};
    const tolerance = 1e-8;

    expectAlmostEqual(actual, expected, tolerance);
  });
});
