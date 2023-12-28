const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('vproj', function() {
  it('should compute the projection of one 3-dimensional vector onto another \
3-dimensional vector.', function() {

    // From:
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vproj_c.html

    const a = [6, 6, 6];
    const b = [2, 0, 0];
    
    const actual = spice.vproj(a, b);
    
    const expected = [6, 0, 0];
    const tolerance = 1e-5; // Define a suitable tolerance
    expectAlmostEqual(actual, expected, tolerance); 
  });
});
