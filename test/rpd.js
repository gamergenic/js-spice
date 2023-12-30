const expect = require('chai').expect;
const { spice } = require('..');

describe('rpd', function() {
  it('should return the number of radians per degree.',
   function() {

    // From:
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/rpd_c.html
    const actual = spice.rpd();
    const pi = 3.141592653589793238462643383279502884197;
    const tolerance = 1e-8;
    expect(actual).to.be.closeTo(pi/180, tolerance); 
  });
});
