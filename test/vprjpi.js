const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('vprjpi', function() {
  it('should find the vector in a specified plane that maps to a specified \
vector in another plane under orthogonal projection.', function() {
    
    // From:
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vprjpi_c.html
    const vin = [0, 1, 0];
    const projpl = spice.nvc2pl([0,0,1], 0);
    const invpl = spice.nvc2pl([0,2,2], 4);

    const actual = spice.vprjpi(vin, projpl, invpl);
    
    const expected = [0, 1, 1];
    const tolerance = 1e-5; // Define a suitable tolerance
    expectAlmostEqual(actual, expected, tolerance); 
  });
});
