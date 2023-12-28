const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./expectAlmostEqual');

describe('vprjp', function() {
  it('should project a vector onto a specified plane, orthogonally.', function() {
    
    // From:
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vprjp_c.html
    const norm = [0, 0, 1];
    const orig = [0, 0, 0];
    const ringpl = spice.nvp2pl(norm, orig);

    const scpos = [ -29703.16955, 879765.72163, -137280.21757 ];
    const actual = spice.vprjp(scpos, ringpl);
    
    const expected = [-29703.16955, 879765.72163, 0.00000];
    const tolerance = 1e-5; // Define a suitable tolerance
    expectAlmostEqual(actual, expected, tolerance); 
  });
});
