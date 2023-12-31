const expect = require('chai').expect;
const { spice } = require('..');

describe('b1950', function() {
  it('should return the Julian Date corresponding to Besselian Date 1950.0.',
   function() {

    // From:
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/b1950_c.html
    const actual = spice.b1950();

    const expected = 2433282.42345905;
    const tolerance = 1e-4;
    expect(actual).to.be.closeTo(expected, tolerance); 
  });
});
