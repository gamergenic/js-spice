const expect = require('chai').expect;
const { spice } = require('..');

describe('b1900', function() {
  it('should return the Julian Date corresponding to Besselian Date 1900.0.',
   function() {

    // From:
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/b1900_c.html
    const actual = spice.b1900();

    const expected = 2415020.31352000;
    const tolerance = 1e-4;
    expect(actual).to.be.closeTo(expected, tolerance); 
  });
});
