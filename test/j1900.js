const expect = require('chai').expect;
const { spice } = require('..');

describe('j1900', function() {
  it('should return the Julian Date of 1899 DEC 31 12:00:00 (1900 JAN 0.5).',
   function() {

    // From:
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/j1900_c.html
    const actual = spice.j1900();

    const expected = 2415020.00000000;
    const tolerance = 1e-8;
    expect(actual).to.be.closeTo(expected, tolerance); 
  });
});
