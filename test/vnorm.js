const expect = require('chai').expect;
const { spice } = require('..');

describe('vnorm', function() {
  it('should compute the magnitude of a double precision 3-dimensional vector.',
   function() {

    const v1 = [1,  2,  2,];
    
    const actual = spice.vnorm(v1);

    const expected = 3;
    const tolerance = 1e-5;
    expect(actual).to.be.closeTo(expected, tolerance);
  });
});
