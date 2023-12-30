const expect = require('chai').expect;
const { spice } = require('..');

describe('vdist', function() {
  it('should return the distance between two three-dimensional vectors.',
   function() {

    // from:
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vdist_c.html
    const v1 = [1.0, 0.0, 0.0];
    const v2 = [0.0, 1.0, 0.0];
    
    const actual = spice.vdist(v1, v2);

    const expected = 1.414214;
    const tolerance = 1e-5;
    expect(actual).to.be.closeTo(expected, tolerance);
  });
});
