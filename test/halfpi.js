const expect = require('chai').expect;
const { spice } = require('..');

describe('halfpi', function() {
  it('should return half the value of pi.',
   function() {

    // From:
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/halfpi_c.html
    const actual = spice.halfpi();

    const expected = 1.5707963267948965579990;
    const tolerance = 1e-8;
    expect(actual).to.be.closeTo(expected, tolerance); 
  });
});
