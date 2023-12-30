const expect = require('chai').expect;
const { spice } = require('..');

describe('j2000', function() {
  it('should return the Julian Date of 2000 JAN 01 12:00:00 (2000 JAN 1.5).',
   function() {

    // From:
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/j2000_c.html
    const actual = spice.j2000();

    const expected = 2451545.00000000;
    const tolerance = 1e-8;
    expect(actual).to.be.closeTo(expected, tolerance); 
  });
});
