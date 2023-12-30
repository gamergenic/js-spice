const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('mxm', function() {
  it('should multiply two 3x3 matrices', function() {
    let m1 = [[1, 2, 3], [4,5,6], [7,8,9]];
    let m2 = [[1, 0, 0], [0,1,0], [0,0,1]];

    let actual = spice.mxm(m1, m2);

    let expected = [[1, 2, 3], [4,5,6], [7,8,9]];

    const tolerance = 1e-8;
    expectAlmostEqual(actual, expected, tolerance);
  });
});
