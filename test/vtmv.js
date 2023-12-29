const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('vtmv', function() {
  it('should multiply the transpose of a 3-dimensional column vector, \
a 3x3 matrix, and a 3-dimensional column vector.',
   function() {

    const v1 = [2, 4, 6];;
    const matrix = [[ 0, 1, 0],
                    [-1, 0, 0],
                    [ 0, 0, 1]];
    const v2 = [1, 1, 1];
    
    const actual = spice.vtmv(v1, matrix, v2);

    const expected = 4;
    const tolerance = 1e-5;
    expect(actual).to.be.closeTo(expected, tolerance);
  });
});
