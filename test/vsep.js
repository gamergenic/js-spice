const expect = require('chai').expect;
const { spice } = require('..');

describe('vsep', function() {
  it('should find the separation angle in radians between two double \
precision, 3-dimensional vectors.', function() {

    const v1 = [1, 0, 0];
    const v2 = [0, 1, 0];
    
    const actual = spice.vsep(v1, v2);
    const expected = 3.1415926536 / 2;
    const tolerance = 1e-5;
    expect(actual).to.be.closeTo(expected, tolerance);
  });
});
