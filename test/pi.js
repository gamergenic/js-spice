const expect = require('chai').expect;
const { spice } = require('..');

describe('pi', function() {
  it('should return the value of pi.',
   function() {

    // From:
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/pi_c.html
    const actual = spice.pi();
    const pi = 3.141592653589793238462643383279502884197;
    const tolerance = 1e-8;
    expect(actual).to.be.closeTo(pi, tolerance); 
  });
});
