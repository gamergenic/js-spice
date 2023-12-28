const expect = require('chai').expect;
const { spice } = require('..');

describe('vrel', function() {
  it('should return the relative difference between two 3-dimensional vectors.', function() {

    const v1 = [1, 2, 3];
    const v2 = [4, 5, 6];
    
    const actual = spice.vrel(v1, v2);
    
    const expected = 0.592156525463792;
    const tolerance = 1e-5; // Define a suitable tolerance
    expect(actual).to.be.closeTo(expected, tolerance);
  });
});
