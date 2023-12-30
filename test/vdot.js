const expect = require('chai').expect;
const { spice } = require('..');

describe('vdot', function() {
  it('should compute the dot product of two double precision, 3-dimensional vectors.',
   function() {

    // from:
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vdist_c.html
    const v1 = [1, 2, 3];
    const v2 = [4, 5, 6];
    
    const actual = spice.vdot(v1, v2);

    const expected = 1*4 + 2*5 + 3*6;
    const tolerance = 1e-5;
    expect(actual).to.be.closeTo(expected, tolerance);
  });
});
